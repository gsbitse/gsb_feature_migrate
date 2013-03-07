<?php

/**
 * @file
 * File ID replace Feeds Tamper plugin.
 *
 * Used to replace old "fid" values in fields with new "fid" values of imported files.
 */
$plugin = array(
  'form' => 'gsb_feature_migrate_file_id_replace_form',
  'callback' => 'gsb_feature_migrate_file_id_replace_callback',
  'name' => 'File ID replace',
  'multi' => 'direct',
  'category' => 'Text',
);

function gsb_feature_migrate_file_id_replace_form($importer, $element_key, $settings) {
  $form = array();

  $form['html'] = array(
    '#markup' => t('Replace old file id with new ones, we use uri as unique field for mapping.')
  );

  $form['services_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Resource url pattern that returns file object, use $fid as file id placeholder. Example: rm/entity_file.json?param[fid]=$fid'),
    '#default_value' => 'rm/entity_file.json?param[fid]=$fid',
  );

  return $form;
}

function gsb_feature_migrate_file_id_replace_callback($result, $item_key, $element_key, &$field, $settings) {
  $fid_regex = '/"fid":"(\d+)"/';

  // Find all fids in the body
  preg_match_all($fid_regex, $field, $matches);

  foreach ($matches[1] as $delta => $old_fid) {
    $request_url = str_replace('$fid', $old_fid, $settings['services_url']);

    // Parse fetcher input url to get hostname to query for file entities.
    $parts = parse_url($result->link);
    if ($parts) {
      $port = isset($parts['port']) ? ':' . $parts['port'] : '';
      $url = $parts['scheme'] . '://' . $parts['host'] . $port;
      $request_url = $url . '/' . $request_url;
    }

    $response = drupal_http_request($request_url);
    if ($response->code == 200) {
      $old_file = json_decode($response->data);
      $new_file = file_uri_to_object($old_file[0]->uri);
      $field = str_replace('"fid":"' . $old_fid . '"', '"fid":"' . $new_file->fid . '"', $field);
    }
  }
}
