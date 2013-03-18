<?php
/**
 * @file
 * gsb_feature_migrate.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function gsb_feature_migrate_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'business_insights';
  $feeds_importer->config = array(
    'name' => 'Business Insights',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsCrawler',
      'config' => array(
        'auto_detect_feeds' => 0,
        'use_pubsubhubbub' => 0,
        'designated_hub' => '',
        'crawler' => array(
          'num_pages' => 0,
          'delay' => '1',
          'first_run' => '0',
          'auto' => '0',
          'xpath' => '',
          'url' => array(
            'url_pattern' => 'http://sfordsbox.prod.acquia-sites.com/rm/entity_node.json?page=$index&pagesize=50&params[type]=research',
            'initial' => '0',
            'increment' => '1',
          ),
        ),
        'crawled' => FALSE,
        'request_timeout' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.*',
        'sources' => array(
          'jsonpath_parser:0' => 'nid',
          'jsonpath_parser:1' => 'title',
          'jsonpath_parser:2' => 'body.und.*.value',
          'jsonpath_parser:3' => 'field_date.und.*.value',
          'jsonpath_parser:4' => 'field_res_teaser.und.*.value',
          'jsonpath_parser:5' => 'field_res_image.und.*.uri',
          'jsonpath_parser:6' => 'field_res_image.und.*.title',
          'jsonpath_parser:7' => 'field_res_image.und.*.alt',
          'jsonpath_parser:8' => 'field_res_caption.und.*.value',
          'jsonpath_parser:9' => 'field_res_rlinks.und.*.title',
          'jsonpath_parser:10' => 'field_res_rlinks.und.*.url',
          'jsonpath_parser:11' => 'path',
          'jsonpath_parser:12' => 'created',
          'jsonpath_parser:13' => 'status',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:8' => 0,
            'jsonpath_parser:9' => 0,
            'jsonpath_parser:10' => 0,
            'jsonpath_parser:11' => 0,
            'jsonpath_parser:12' => 0,
            'jsonpath_parser:13' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'nid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'body',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_date_published:start',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_editorial_summary',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_content_image:uri',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_content_image:title',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_content_image:alt',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_content_image_caption',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'jsonpath_parser:9',
            'target' => 'field_related_links:title',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'jsonpath_parser:10',
            'target' => 'field_related_links:url',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'jsonpath_parser:11',
            'target' => 'path_alias',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'jsonpath_parser:12',
            'target' => 'created',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'jsonpath_parser:13',
            'target' => 'status',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'panopoly_wysiwyg_text',
        'skip_hash_check' => 0,
        'bundle' => 'business_insight',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['business_insights'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'files';
  $feeds_importer->config = array(
    'name' => 'Files',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.*',
        'sources' => array(
          'jsonpath_parser:1' => 'uri',
          'jsonpath_parser:2' => '',
          'jsonpath_parser:3' => '',
          'jsonpath_parser:4' => 'type',
          'jsonpath_parser:5' => 'uri',
          'jsonpath_parser:6' => 'filename',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsFileProcessor',
      'config' => array(
        'file_type' => 'image',
        'author' => '1',
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'guid',
            'unique' => 0,
          ),
          1 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'field_file_image_title_text',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_file_image_alt_text',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'type',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'uri',
            'unique' => 1,
          ),
          5 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'filename',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Blank source 1',
            'target' => 'field_sections',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'panopoly_wysiwyg_text',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['files'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'media_mention';
  $feeds_importer->config = array(
    'name' => 'Newsmakers to Media Mention',
    'description' => 'Newsmakers to Media Mention migration',
    'fetcher' => array(
      'plugin_key' => 'FeedsCrawler',
      'config' => array(
        'auto_detect_feeds' => 0,
        'use_pubsubhubbub' => 0,
        'designated_hub' => '',
        'crawler' => array(
          'num_pages' => 0,
          'delay' => '1',
          'first_run' => '0',
          'auto' => '0',
          'xpath' => '',
          'url' => array(
            'url_pattern' => 'http://sfordsbox.prod.acquia-sites.com/rm/entity_node.json?page=$index&pagesize=10&params[type]=newsmakers',
            'initial' => '0',
            'increment' => '1',
          ),
        ),
        'crawled' => FALSE,
        'request_timeout' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.*',
        'sources' => array(
          'jsonpath_parser:0' => 'nid',
          'jsonpath_parser:1' => 'title',
          'jsonpath_parser:2' => 'path',
          'jsonpath_parser:3' => 'status',
          'jsonpath_parser:4' => 'created',
          'jsonpath_parser:5' => 'field_date.und.*.value',
          'jsonpath_parser:6' => 'field_newsmakers_image.und.*.uri',
          'jsonpath_parser:7' => 'field_newsmakers_image.und.*.alt',
          'jsonpath_parser:8' => 'field_newsmakers_image.und.*.title',
          'jsonpath_parser:9' => 'field_newsmakers_image.und.*.title',
          'jsonpath_parser:10' => 'field_source_publication.und.*.value',
          'jsonpath_parser:11' => 'field_url.und.*.value',
          'jsonpath_parser:12' => 'field_teaser.und.*.value',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:8' => 0,
            'jsonpath_parser:9' => 0,
            'jsonpath_parser:10' => 0,
            'jsonpath_parser:11' => 0,
            'jsonpath_parser:12' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'nid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'path_alias',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'status',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'created',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_date_published:start',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_content_image:uri',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_content_image:alt',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_content_image:title',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'jsonpath_parser:9',
            'target' => 'field_content_image_caption',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'jsonpath_parser:10',
            'target' => 'field_source_link:title',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'jsonpath_parser:11',
            'target' => 'field_source_link:url',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'jsonpath_parser:12',
            'target' => 'field_editorial_summary',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'panopoly_wysiwyg_text',
        'skip_hash_check' => 0,
        'bundle' => 'gsb_media_mention',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['media_mention'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'news';
  $feeds_importer->config = array(
    'name' => 'News',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsCrawler',
      'config' => array(
        'auto_detect_feeds' => 0,
        'use_pubsubhubbub' => 0,
        'designated_hub' => '',
        'crawler' => array(
          'num_pages' => '1',
          'delay' => '1',
          'first_run' => '1',
          'auto' => '0',
          'xpath' => '',
          'url' => array(
            'url_pattern' => 'http://sfordsbox.prod.acquia-sites.com/rm/entity_node.json?page=$index&pagesize=50&params[type]=news',
            'initial' => '0',
            'increment' => '1',
          ),
        ),
        'crawled' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.*',
        'sources' => array(
          'jsonpath_parser:0' => 'nid',
          'jsonpath_parser:1' => 'nid',
          'jsonpath_parser:2' => 'title',
          'jsonpath_parser:3' => 'body.und.*.value',
          'jsonpath_parser:4' => '',
          'jsonpath_parser:5' => 'field_content_image.und.*.uri',
          'jsonpath_parser:6' => 'field_content_image.und.*.alt',
          'jsonpath_parser:7' => 'field_content_image.und.*.title',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'gsb_news',
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'nid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'guid',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'body',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'uid',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_news_image:uri',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_news_image:alt',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_news_image:title',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'panopoly_wysiwyg_text',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['news'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'ranking_to_media_mention';
  $feeds_importer->config = array(
    'name' => 'Ranking to Media Mention',
    'description' => 'Ranking to Media Mention migration',
    'fetcher' => array(
      'plugin_key' => 'FeedsCrawler',
      'config' => array(
        'auto_detect_feeds' => 0,
        'use_pubsubhubbub' => 0,
        'designated_hub' => '',
        'crawler' => array(
          'num_pages' => 0,
          'delay' => '1',
          'first_run' => '0',
          'auto' => '0',
          'xpath' => '',
          'url' => array(
            'url_pattern' => 'http://sfordsbox.prod.acquia-sites.com/rm/entity_node.json?page=$index&pagesize=10&params[type]=ranking',
            'initial' => '0',
            'increment' => '1',
          ),
        ),
        'crawled' => FALSE,
        'request_timeout' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.*',
        'sources' => array(
          'jsonpath_parser:0' => 'nid',
          'jsonpath_parser:1' => 'title',
          'jsonpath_parser:2' => 'path',
          'jsonpath_parser:3' => 'status',
          'jsonpath_parser:4' => 'created',
          'jsonpath_parser:5' => 'field_ranking_date.und.*.value',
          'jsonpath_parser:6' => 'field_ranking_publication.und.*.uri',
        ),
        'debug' => array(
          'options' => array(
            'context' => 0,
            'jsonpath_parser:0' => 0,
            'jsonpath_parser:1' => 0,
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'nid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:1',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'path_alias',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'status',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'created',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'field_date_published:start',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_source_publication',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'panopoly_wysiwyg_text',
        'skip_hash_check' => 0,
        'bundle' => 'gsb_media_mention',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['ranking_to_media_mention'] = $feeds_importer;

  return $export;
}
