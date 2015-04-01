<?php
/**
 * @file
 * feature_hcl_campaign.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function feature_hcl_campaign_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create content_type_hcl_campaign_quiz content'.
  $permissions['create content_type_hcl_campaign_quiz content'] = array(
    'name' => 'create content_type_hcl_campaign_quiz content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any content_type_hcl_campaign_quiz content'.
  $permissions['delete any content_type_hcl_campaign_quiz content'] = array(
    'name' => 'delete any content_type_hcl_campaign_quiz content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own content_type_hcl_campaign_quiz content'.
  $permissions['delete own content_type_hcl_campaign_quiz content'] = array(
    'name' => 'delete own content_type_hcl_campaign_quiz content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any content_type_hcl_campaign_quiz content'.
  $permissions['edit any content_type_hcl_campaign_quiz content'] = array(
    'name' => 'edit any content_type_hcl_campaign_quiz content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own content_type_hcl_campaign_quiz content'.
  $permissions['edit own content_type_hcl_campaign_quiz content'] = array(
    'name' => 'edit own content_type_hcl_campaign_quiz content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
