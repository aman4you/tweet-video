<?php
/**
 * @file
 * feature_hcl_campaign.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function feature_hcl_campaign_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_content_type_hcl_campaign_quiz';
  $strongarm->value = 'edit-auto-nodetitle';
  $export['additional_settings__active_tab_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_content_type_hcl_campaign_quiz';
  $strongarm->value = '1';
  $export['ant_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_content_type_hcl_campaign_quiz';
  $strongarm->value = '';
  $export['ant_pattern_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_content_type_hcl_campaign_quiz';
  $strongarm->value = 0;
  $export['ant_php_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_content_type_hcl_campaign_quiz';
  $strongarm->value = 0;
  $export['comment_anonymous_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_content_type_hcl_campaign_quiz';
  $strongarm->value = '1';
  $export['comment_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_content_type_hcl_campaign_quiz';
  $strongarm->value = 0;
  $export['comment_default_mode_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_content_type_hcl_campaign_quiz';
  $strongarm->value = '10';
  $export['comment_default_per_page_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_content_type_hcl_campaign_quiz';
  $strongarm->value = 0;
  $export['comment_form_location_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_content_type_hcl_campaign_quiz';
  $strongarm->value = '0';
  $export['comment_preview_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_content_type_hcl_campaign_quiz';
  $strongarm->value = 0;
  $export['comment_subject_field_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_content_type_hcl_campaign_quiz';
  $strongarm->value = array();
  $export['menu_options_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_content_type_hcl_campaign_quiz';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_content_type_hcl_campaign_quiz';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_content_type_hcl_campaign_quiz';
  $strongarm->value = '0';
  $export['node_preview_content_type_hcl_campaign_quiz'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_content_type_hcl_campaign_quiz';
  $strongarm->value = 0;
  $export['node_submitted_content_type_hcl_campaign_quiz'] = $strongarm;

  return $export;
}
