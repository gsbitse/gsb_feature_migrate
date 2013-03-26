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
  gsb_feature_migrate_import_taxonomy($form_state['complete form']['upload']['#file']->uri);
}

/**
 * Migrate callback.
 *
 * Create terms with term ids in mapped vocabularies.
 * Perform additional tasks before taxonomy import.
 */
function gsb_feature_migrate_import_taxonomy($url) {
  $file = fopen($url, 'r');

  $vocabulary_mappings = gsb_feature_migrate_taxonomy_get_vocabulary_mappings();

  while (($line = fgetcsv($file, 4096, ',', '"')) != FALSE) {
    list($tid, $vid, $name, $weight, $parent) = $line;

    if (array_key_exists($vid, $vocabulary_mappings)) {
      $vid = $vocabulary_mappings[$vid];
      $term = new stdClass();
      $term->tid = $tid;
      $term->vid = $vid;
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
    15 => 'discipline',  // Function -> Discipline
    18 => 'business_insight_topic',  // Principle -> Business Insight Topic
    16 => 'industry',  // Industry -> Industry
    17 => 'region', // Region -> Region
    19 => 'company_organization',  // Company -> Company/Organization
    46 => 'tag', // Tag -> Tag
  );

  foreach ($mappings as $old_vid => $new_vocabulary_name) {
    $new_vocabulary = taxonomy_vocabulary_machine_name_load($new_vocabulary_name);
    $mappings[$old_vid] = $new_vocabulary->vid;
  }

  return $mappings;
}