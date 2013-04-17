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
  $feeds_tamper->id = 'business_insights-jsonpath_parser_4-strip_tags';
  $feeds_tamper->importer = 'business_insights';
  $feeds_tamper->source = 'jsonpath_parser:4';
  $feeds_tamper->plugin_id = 'strip_tags';
  $feeds_tamper->settings = array(
    'allowed_tags' => '',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Strip tags';
  $export['business_insights-jsonpath_parser_4-strip_tags'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'faculty-blank_source_1-rewrite';
  $feeds_tamper->importer = 'faculty';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => '[jsonpath_parser:1]-[jsonpath_parser:5]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';
  $export['faculty-blank_source_1-rewrite'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'faculty-blank_source_2-set_default_value';
  $feeds_tamper->importer = 'faculty';
  $feeds_tamper->source = 'Blank source 2';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => '1',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set default value';
  $export['faculty-blank_source_2-set_default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'faculty-jsonpath_parser_1-rewrite';
  $feeds_tamper->importer = 'faculty';
  $feeds_tamper->source = 'jsonpath_parser:1';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => '[jsonpath_parser:9] [jsonpath_parser:10] [jsonpath_parser:11]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Full name';
  $export['faculty-jsonpath_parser_1-rewrite'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'media_mention-jsonpath_parser_12-strip_tags';
  $feeds_tamper->importer = 'media_mention';
  $feeds_tamper->source = 'jsonpath_parser:12';
  $feeds_tamper->plugin_id = 'strip_tags';
  $feeds_tamper->settings = array(
    'allowed_tags' => '',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Strip tags';
  $export['media_mention-jsonpath_parser_12-strip_tags'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_press_releases_to_news-blank_source_1-set_default_value';
  $feeds_tamper->importer = 'news_press_releases_to_news';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'press-release',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set default value';
  $export['news_press_releases_to_news-blank_source_1-set_default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_press_releases_to_news-jsonpath_parser_2-file_id_replace';
  $feeds_tamper->importer = 'news_press_releases_to_news';
  $feeds_tamper->source = 'jsonpath_parser:2';
  $feeds_tamper->plugin_id = 'file_id_replace';
  $feeds_tamper->settings = array(
    'services_url' => 'rm/entity_file.json?param[fid]=$fid',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'File ID replace';
  $export['news_press_releases_to_news-jsonpath_parser_2-file_id_replace'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_press_releases_to_news-jsonpath_parser_4-strip_tags';
  $feeds_tamper->importer = 'news_press_releases_to_news';
  $feeds_tamper->source = 'jsonpath_parser:4';
  $feeds_tamper->plugin_id = 'strip_tags';
  $feeds_tamper->settings = array(
    'allowed_tags' => '',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Strip tags';
  $export['news_press_releases_to_news-jsonpath_parser_4-strip_tags'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_to_business_insight-jsonpath_parser_2-file_id_replace';
  $feeds_tamper->importer = 'news_to_business_insight';
  $feeds_tamper->source = 'jsonpath_parser:2';
  $feeds_tamper->plugin_id = 'file_id_replace';
  $feeds_tamper->settings = array(
    'services_url' => 'rm/entity_file.json?param[fid]=$fid',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'File ID replace';
  $export['news_to_business_insight-jsonpath_parser_2-file_id_replace'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_to_business_insight-jsonpath_parser_4-strip_tags';
  $feeds_tamper->importer = 'news_to_business_insight';
  $feeds_tamper->source = 'jsonpath_parser:4';
  $feeds_tamper->plugin_id = 'strip_tags';
  $feeds_tamper->settings = array(
    'allowed_tags' => '',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Strip tags';
  $export['news_to_business_insight-jsonpath_parser_4-strip_tags'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_to_school_story-blank_source_1-set_default_value';
  $feeds_tamper->importer = 'news_to_school_story';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'school-news',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set default value';
  $export['news_to_school_story-blank_source_1-set_default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_to_school_story-jsonpath_parser_2-file_id_replace';
  $feeds_tamper->importer = 'news_to_school_story';
  $feeds_tamper->source = 'jsonpath_parser:2';
  $feeds_tamper->plugin_id = 'file_id_replace';
  $feeds_tamper->settings = array(
    'services_url' => 'rm/entity_file.json?param[fid]=$fid',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'File ID replace';
  $export['news_to_school_story-jsonpath_parser_2-file_id_replace'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'news_to_school_story-jsonpath_parser_4-strip_tags';
  $feeds_tamper->importer = 'news_to_school_story';
  $feeds_tamper->source = 'jsonpath_parser:4';
  $feeds_tamper->plugin_id = 'strip_tags';
  $feeds_tamper->settings = array(
    'allowed_tags' => '',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Strip tags';
  $export['news_to_school_story-jsonpath_parser_4-strip_tags'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'publications-jsonpath_parser_1-strip_tags';
  $feeds_tamper->importer = 'publications';
  $feeds_tamper->source = 'jsonpath_parser:1';
  $feeds_tamper->plugin_id = 'strip_tags';
  $feeds_tamper->settings = array(
    'allowed_tags' => '',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Strip tags';
  $export['publications-jsonpath_parser_1-strip_tags'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'publications-jsonpath_parser_3-year_to_date_convert';
  $feeds_tamper->importer = 'publications';
  $feeds_tamper->source = 'jsonpath_parser:3';
  $feeds_tamper->plugin_id = 'year_to_date';
  $feeds_tamper->settings = '';
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Year to Date convert';
  $export['publications-jsonpath_parser_3-year_to_date_convert'] = $feeds_tamper;

  return $export;
}
