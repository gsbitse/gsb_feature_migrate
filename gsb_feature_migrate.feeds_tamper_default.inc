<?php
/**
 * @file
 * gsb_feature_migrate.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function gsb_feature_migrate_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'business_insights-jsonpath_parser_2-file_id_replace';
  $feeds_tamper->importer = 'business_insights';
  $feeds_tamper->source = 'jsonpath_parser:2';
  $feeds_tamper->plugin_id = 'file_id_replace';
  $feeds_tamper->settings = array(
    'services_url' => 'rm/entity_file.json?param[fid]=$fid',
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'File ID replace';
  $export['business_insights-jsonpath_parser_2-file_id_replace'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news-jsonpath_parser_3-file_id_replace';
  $feeds_tamper->importer = 'news';
  $feeds_tamper->source = 'jsonpath_parser:3';
  $feeds_tamper->plugin_id = 'file_id_replace';
  $feeds_tamper->settings = array(
    'services_url' => 'rm/entity_file.json?param[fid]=$fid',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'File ID replace';
  $export['news-jsonpath_parser_3-file_id_replace'] = $feeds_tamper;

  return $export;
}
