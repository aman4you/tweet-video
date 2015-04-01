<?php
/**
 * @file
 * HCL Campaign Admin Configuration.
 */

/**
 * HCL Campaign Admin Configuration form.
 *
 * @return html
 *   HTML Form of HCL Campaign Admin Configuration form.
 */
function hcl_campaign_configuration($form, &$form_state) {

  $video_destination = COPERATE_VIDEO_PATH . '/videos';
  $image_destination = COPERATE_VIDEO_PATH . '/images';

  $hcl_tweets_data = variable_get('hcl_tweets_data', '');

  $form['hcl-campaign-configuration-wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('tweets-count-container-wrapper'),
    ),
  );

  $form_state['storage']['twitter_tweet_count'] = 7;

  for ($i=1; $i <= $form_state['storage']['twitter_tweet_count']; $i++) {

    $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('tweets-count-container'),
      ),
    );

    $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i]['hcl_tweets_count_counter'] = array(
      '#markup' => '<div class="tweets_count_lable">' . t('Part ' . $i) . '</div>',
      '#attributes' => array(
        'class' => array('tweets_count_counter'),
      ),
    );

    $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i]['hcl_tweets_count_' . $i] = array(
      '#type' => 'textfield',
      '#title' => t('Tweet Counts'),
      '#title_display' => 'invisible',
      '#default_value' => isset($hcl_tweets_data['hcl_tweets_count']['hcl_tweets_count_' . $i]) ? $hcl_tweets_data['hcl_tweets_count']['hcl_tweets_count_' . $i] : '',
      '#maxlength' => 10,
      '#size' => 15,
      '#element_validate' => array('element_validate_integer_positive'),
      '#attributes' => array(
        'class' => array('tweets_count'),
        'placeholder' => t('Tweet Counts'),
      ),
    );

    if (!file_prepare_directory($video_destination)) {
      drupal_mkdir($video_destination, NULL, TRUE);
    }

    $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i]['hcl_tweets_video_' . $i] = array(
      '#type' => 'managed_file',
      '#title' => t('Video'),
      '#title_display' => 'invisible',
      '#default_value' => isset($hcl_tweets_data['hcl_tweets_video']['hcl_tweets_video_' . $i]) ? $hcl_tweets_data['hcl_tweets_video']['hcl_tweets_video_' . $i] : 0,
      '#tree' => FALSE,
      '#upload_validators' => array(
        'file_validate_extensions' => array('mp4'),
      ),
      '#upload_location' => $video_destination,
      '#attributes' => array(
        'class' => array('video'),
      ),
    );

    $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i]['hcl_tweets_image_preview_' . $i] = array(
      '#type' => 'managed_file',
      '#title' => t('Video Preview Image'),
      '#title_display' => 'invisible',
      '#default_value' => isset($hcl_tweets_data['hcl_tweets_image_preview']['hcl_tweets_image_preview_' . $i]) ? $hcl_tweets_data['hcl_tweets_image_preview']['hcl_tweets_image_preview_' . $i] : 0,
      '#tree' => FALSE,
      '#upload_validators' => array(
        'file_validate_extensions' => array('gif png jpg jpeg'),
      ),
      '#upload_location' => $image_destination,
      '#attributes' => array(
        'class' => array('video-preview-image'),
      ),
    );

  }

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'twitter_tweet_count') . '/css/hcl-campaign-configuration.css',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

function hcl_campaign_configuration_validate($form, &$form_state) {

  $element = &$form_state['values'];

  // Validate tweet count.
  for ($i=1; $i <= $form_state['storage']['twitter_tweet_count']; $i++) {
    if (empty($element['hcl_tweets_count_' . $i])) {
      $element['hcl_tweets_count_' . $i] = isset($element['hcl_tweets_count_' . ($i - 1)]) ? $element['hcl_tweets_count_' . ($i - 1)] : $element['hcl_tweets_count_' . $i];
      for ($j=$i+1; $j <= $form_state['storage']['twitter_tweet_count']; $j++) {
        if (!empty($element['hcl_tweets_count_' . $j])) {
          form_set_error('', 'Please fill empty fields');
        }
        $element['hcl_tweets_count_' . $j] = isset($element['hcl_tweets_count_' . ($j - 1)]) ? $element['hcl_tweets_count_' . ($j - 1)] : $element['hcl_tweets_count_' . $j];
      }
    }
  }

  for ($i=1; $i <= $form_state['storage']['twitter_tweet_count']; $i++) {

    // Get video file.
    $validators = $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i]['hcl_tweets_video_' . $i]['#upload_validators'];
    $file = file_save_upload('hcl_tweets_video_' . $i, $validators);
    if (isset($file)) {
      // File upload was attempted.
      if ($file) {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        file_usage_add($file, 'twitter_tweet_count', 'file', $file->fid);
        // Put the temporary file in form_values so we can save it on submit.
        $element['hcl_tweets_video_' . $i] = $file->fid;
      }
    }

    // Get image file.
    $validators = $form['hcl-campaign-configuration-wrapper']['tweets_count_container_' . $i]['hcl_tweets_image_preview_' . $i]['#upload_validators'];
    $file = file_save_upload('hcl_tweets_image_preview_' . $i, $validators);
    if (isset($file)) {
      // File upload was attempted.
      if ($file) {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        file_usage_add($file, 'twitter_tweet_count', 'file', $file->fid);
        // Put the temporary file in form_values so we can save it on submit.
        $element['hcl_tweets_image_preview_' . $i] = $file->fid;
      }
    }
  }

  // Validate video.
  for ($i=1; $i <= $form_state['storage']['twitter_tweet_count']; $i++) {
    if (empty($element['hcl_tweets_video_' . $i])) {
      for ($j=$i+1; $j <= $form_state['storage']['twitter_tweet_count']; $j++) {
        if (!empty($element['hcl_tweets_video_' . $j])) {
          form_set_error('', 'Please fill empty fields');
        }
      }
    }
  }

  // Validate video image preview.
  for ($i=1; $i <= $form_state['storage']['twitter_tweet_count']; $i++) {
    if (empty($element['hcl_tweets_image_preview_' . $i])) {
      for ($j=$i+1; $j <= $form_state['storage']['twitter_tweet_count']; $j++) {
        if (!empty($element['hcl_tweets_image_preview_' . $j])) {
          form_set_error('', 'Please fill empty fields');
        }
      }
    }
  }

}

function hcl_campaign_configuration_submit($form, &$form_state) {

  $element = &$form_state['values'];
  for ($i=1; $i <= $form_state['storage']['twitter_tweet_count']; $i++) {
    $data['hcl_tweets_count']['hcl_tweets_count_' . $i] = !empty($element['hcl_tweets_count_' . $i]) ? $element['hcl_tweets_count_' . $i] : '';
    $data['hcl_tweets_video']['hcl_tweets_video_' . $i] = !empty($element['hcl_tweets_video_' . $i]) ? $element['hcl_tweets_video_' . $i] : 0;
    $data['hcl_tweets_image_preview']['hcl_tweets_image_preview_' . $i] = !empty($element['hcl_tweets_image_preview_' . $i]) ? $element['hcl_tweets_image_preview_' . $i] : 0;
  }

  if (isset($data)) {
    variable_set('hcl_tweets_data', $data);
  }
}

function hcl_campaign_hashtag_configuration($form, &$form_state) {

  $form['hcl_campaign_twitter_customer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Customer Key'),
    '#default_value' => variable_get('hcl_campaign_twitter_customer_key', ''),
    '#size' => 35,
  );

  $form['hcl_campaign_twitter_customer_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Customer Secret'),
    '#default_value' => variable_get('hcl_campaign_twitter_customer_secret', ''),
    '#size' => 35,
  );

  $form['hcl_campaign_twitter_access_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Access Token'),
    '#default_value' => variable_get('hcl_campaign_twitter_access_token', ''),
    '#size' => 35,
  );

  $form['hcl_campaign_twitter_access_token_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Access Token Secret'),
    '#default_value' => variable_get('hcl_campaign_twitter_access_token_secret', ''),
    '#size' => 35,
  );

  return system_settings_form($form);
}

/**
 * Check hashtag string with #.
 */
function hcl_campaign_hashtag_validate(&$element, &$form_state) {
  $old_hashtag = variable_get('hcl_campaign_hashtag', '');
  $hashtag = &$form_state['values']['hcl_campaign_hashtag'];
  if (substr($hashtag, 0, 1) != "#") {
    $hashtag = '#' . $hashtag;
  }
  if (strcmp($old_hashtag, $hashtag) == 0) {
    variable_del('hcl_tweets_since_id', 0);
    variable_set('hcl_tweets_total_count', 0);
  }

}

function hcl_campaign_tweet_widget_configuration($form, &$form_state) {

  $form['hcl_campaign_hashtag'] = array(
    '#type' => 'textfield',
    '#title' => t('HashTag #'),
    '#default_value' => variable_get('hcl_campaign_hashtag', ''),
    '#element_validate' => array('hcl_campaign_hashtag_validate'),
    '#size' => 25,
  );

  $form['hcl_campaign_twitter_widget_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Widget ID'),
    '#default_value' => variable_get('hcl_campaign_twitter_widget_id', ''),
    '#size' => 35,
  );

  $form['hcl_campaign_about_contest'] = array(
    '#type' => 'textarea',
    '#title' => t('About Contest'),
    '#default_value' => variable_get('hcl_campaign_about_contest', ''),
  );

  return system_settings_form($form);
}
