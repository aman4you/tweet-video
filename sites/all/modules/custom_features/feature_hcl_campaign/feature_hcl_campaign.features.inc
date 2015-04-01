<?php
/**
 * @file
 * feature_hcl_campaign.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_hcl_campaign_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function feature_hcl_campaign_node_info() {
  $items = array(
    'content_type_hcl_campaign_quiz' => array(
      'name' => t('hcl campaign quiz'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
