<?php

/**
 * @file
 * Year To Date convert Feeds Tamper plugin.
 *
 * Used to convert numeric year values to date format.
 */

$plugin = array(
  'form' => 'gsb_feature_migrate_year_to_date_form',
  'callback' => 'gsb_feature_migrate_year_to_date_callback',
  'name' => 'Year to Date convert',
  'multi' => 'direct',
  'category' => 'Text',
);

/**
 * Year to Date plugin config form.
 */
function gsb_feature_migrate_year_to_date_form($importer, $element_key, $settings) {
  $form = array();

  $form['html'] = array(
    '#markup' => t('Pass a year and it will be converted to January 1, Year')
  );

  return $form;
}

/**
 * Year to Date plugin callback.
 *
 * Convert Year field to Date.
 */
function gsb_feature_migrate_year_to_date_callback($result, $item_key, $element_key, &$field, $settings) {
  if (is_numeric($field) && strlen($field) == 4) {
    // Hardcode to January 1.
    $field = $field . '-01-01';
  }
}
