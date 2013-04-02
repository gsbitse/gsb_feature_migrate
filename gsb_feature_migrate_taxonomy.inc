<?php

/**
 * Taxonomy import form callback.
 *
 * Upload CSV dump file to import terms.
 */
function gsb_feature_migrate_taxonomy_form() {
  $form = array();

  $form['upload'] = array(
    '#title' => t('Taxonomy Dump'),
    '#type' => 'managed_file',
    '#description' => t('Upload a CSV dump to import taxonomies.'),
    '#upload_location' => 'private://taxonomy_import/',
    '#upload_validators' => array('file_validate_extensions' => array('csv')),
    '#default_value' => variable_get('gsb_feature_migrate_taxonomy_import_fid', ''),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Import',
  );

  return $form;
}

/**
 * Taxonomy import form validate callback.
 *
 * Check if dump file was uploaded and the extension is csv.
 */
function gsb_feature_migrate_taxonomy_form_validate($form, &$form_state) {
  if (!$form_state['values']['upload']) {
    form_set_error('upload', t('Please upload CSV dump for taxonomies import.'));
  }
}

/**
 * Taxonomy import form validate callback.
 *
 * Call import callback.
 */
function gsb_feature_migrate_taxonomy_form_submit($form, &$form_state) {
  variable_set('gsb_feature_migrate_taxonomy_import_fid', $form_state['values']['upload']);
  gsb_feature_migrate_taxonomy_import($form_state['complete form']['upload']['#file']->uri);
}

/**
 * Migrate callback.
 *
 * Create terms with term ids in mapped vocabularies.
 * Perform additional tasks before taxonomy import.
 */
function gsb_feature_migrate_taxonomy_import($url) {
  $file = fopen($url, 'r');

  $vocabulary_mappings = gsb_feature_migrate_taxonomy_get_vocabulary_mappings();
  $vocabulary_names = taxonomy_vocabulary_get_names();

  // Loop throw CSV file.
  while (($line = fgetcsv($file, 4096, ',', '"')) != FALSE) {
    list($tid, $vocabulary_machine_name, $name, $weight, $parent) = $line;
    if (array_key_exists($vocabulary_machine_name, $vocabulary_mappings)) {
      // Work with new vocabulary_machine_name.
      $vocabulary_machine_name = $vocabulary_mappings[$vocabulary_machine_name];

      // In case we find matched terms, replace the tid with old one.
      $matched_terms = taxonomy_get_term_by_name($name, $vocabulary_machine_name);
      if (!empty($matched_terms)) {
        foreach ($matched_terms as $matched_term) {
          _gsb_feature_migrate_taxonomy_replace_tid($matched_term->tid, $tid);
        }
        continue;
      }

      // Otherwise we create new terms.
      $term = new stdClass();
      $term->tid = $tid;
      $term->vid = $vocabulary_names[$vocabulary_machine_name]->vid;
      $term->name = $name;
      $term->weight = $weight;
      $term->parent = $parent;
      $term->is_new = FALSE;
      if (taxonomy_term_load($term->tid) === FALSE) {
        $term->is_new = TRUE;
      }
      // We use our own copy of taxonomy_term_save to preserve tids.
      taxonomy_term_save_tid($term);
    }
  };
}

/**
 * Borrowed from Drupal Core. The callback saves terms with tids if is_new param is set.
 */
function taxonomy_term_save_tid($term) {
  // Prevent leading and trailing spaces in term names.
  $term->name = trim($term->name);
  if (!isset($term->vocabulary_machine_name)) {
    $vocabulary = taxonomy_vocabulary_load($term->vid);
    $term->vocabulary_machine_name = $vocabulary->machine_name;
  }

  // Load the stored entity, if any.
  if (!empty($term->tid) && !isset($term->original)) {
    $term->original = entity_load_unchanged('taxonomy_term', $term->tid);
  }

  field_attach_presave('taxonomy_term', $term);
  module_invoke_all('taxonomy_term_presave', $term);
  module_invoke_all('entity_presave', $term, 'taxonomy_term');

  if (empty($term->tid) || $term->is_new) {
    $op = 'insert';
    $status = drupal_write_record('taxonomy_term_data', $term);
    field_attach_insert('taxonomy_term', $term);
    if (!isset($term->parent)) {
      $term->parent = array(0);
    }
  }
  else {
    $op = 'update';
    $status = drupal_write_record('taxonomy_term_data', $term, 'tid');
    field_attach_update('taxonomy_term', $term);
    if (isset($term->parent)) {
      db_delete('taxonomy_term_hierarchy')
        ->condition('tid', $term->tid)
        ->execute();
    }
  }

  if (isset($term->parent)) {
    if (!is_array($term->parent)) {
      $term->parent = array($term->parent);
    }
    $query = db_insert('taxonomy_term_hierarchy')
      ->fields(array('tid', 'parent'));
    foreach ($term->parent as $parent) {
      if (is_array($parent)) {
        foreach ($parent as $tid) {
          $query->values(array(
            'tid' => $term->tid,
            'parent' => $tid
          ));
        }
      }
      else {
        $query->values(array(
          'tid' => $term->tid,
          'parent' => $parent
        ));
      }
    }
    $query->execute();
  }

  // Reset the taxonomy term static variables.
  taxonomy_terms_static_reset();

  // Invoke the taxonomy hooks.
  module_invoke_all("taxonomy_term_$op", $term);
  module_invoke_all("entity_$op", $term, 'taxonomy_term');
  unset($term->original);

  return $status;
}

/**
 * Default vocabulary mappings configuration.
 */
function gsb_feature_migrate_taxonomy_get_vocabulary_mappings() {
  // Use vocabulary machine_names because vids can change during the builds.
  $mappings = array(
    'function' => 'discipline', // Function -> Discipline
    'principle' => 'business_insight_topic', // Principle -> Business Insight Topic
    'industry' => 'industry', // Industry -> Industry
    'region' => 'region', // Region -> Region
    'company' => 'company_organization', // Company -> Company/Organization
    'tag' => 'tag', // Tag -> Tag
  );

  return $mappings;
}

/**
 * Replace new term id with old one.
 *
 * This is done to preserve URLs and terms associated to nodes.
 *
 */
function _gsb_feature_migrate_taxonomy_replace_tid($existing_tid, $new_tid) {
  // Update term id in taxonomy_term_data table.
  db_update('taxonomy_term_data')->fields(array('tid' => $new_tid))
    ->condition('tid', $existing_tid, '=')
    ->execute();

  // Update term hierarchy with updated tids.
  db_update('taxonomy_term_hierarchy')->fields(array('tid' => $new_tid))
    ->condition('tid', $existing_tid, '=')
    ->execute();
  db_update('taxonomy_term_hierarchy')->fields(array('parent' => $new_tid))
    ->condition('parent', $existing_tid, '=')
    ->execute();

  // Replace aliases.
  $path = path_load('taxonomy/term/' . $existing_tid);
  if ($path !== FALSE) {
    $path['source'] = 'taxonomy/term/' . $new_tid;
    path_save($path);
  }
}
