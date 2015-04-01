<?php

include_once 'lib.php';

$video_name = isset($_REQUEST['video_name']) ? $_REQUEST['video_name'] : '';
$total_tweets_count = isset($_REQUEST['total_tweets_count']) ? $_REQUEST['total_tweets_count'] : '';
$quiz = isset($_REQUEST['quiz']) ? $_REQUEST['quiz'] : '';
$data = twitter_tweets_count($video_name, $total_tweets_count);
$update_quiz_question = isset($quiz) ? is_quiz_question_update($quiz) : TRUE;
$data['is_quiz_question_update'] = $update_quiz_question[0];
$data['update_quiz_question'] = $update_quiz_question[1];
$data['hcl_tweets_count'] = get_twitter_parts();

echo json_encode($data);

function get_twitter_parts() {
  $hcl_tweets_data = variable_get('hcl_tweets_data', '');
  $hcl_tweets_count = isset($hcl_tweets_data['hcl_tweets_count']) ? array_values($hcl_tweets_data['hcl_tweets_count']) : '';

  return $hcl_tweets_count;
}

/**
 * Send all data to client.
 *
 * @param string
 *   Video path.
 *
 * @return array
 *   Data related to videos.
 */
function twitter_tweets_count($video_name, $old_total_tweets_count) {
  $total_tweets_count = variable_get('hcl_tweets_total_count', 0);
  $data['total_tweets_count'] = $total_tweets_count;
  $data['image_name'] = get_hcl_tweet_image_name($data['total_tweets_count']);
  $data['video_name'] = get_hcl_tweet_video_name($data['total_tweets_count']);
  $data['video_name'] = str_replace(' ', '%20', $data['video_name']);
  $data['video_name_change'] = $video_name == $data['video_name'] ? FALSE : TRUE;

  return $data;
}

/**
 * Get video path according to tweets count.
 *
 * @param int $total_tweets_count
 *   Total tweets count.
 *
 * @return string
 *   Video uri.
 */
function get_hcl_tweet_video_name($total_tweets_count) {

  $hcl_tweets_data  = variable_get('hcl_tweets_data', '');

  $hcl_tweets_video = array_values($hcl_tweets_data['hcl_tweets_video']);
  foreach ($hcl_tweets_video as $key => $value) {
    if (empty($value)) {
      $hcl_tweets_video[$key] = isset($hcl_tweets_video[$key - 1]) ? $hcl_tweets_video[$key - 1] : $hcl_tweets_video[$key];
    }
  }
  $hcl_tweets_count = array_values($hcl_tweets_data['hcl_tweets_count']);

  $video_name = 0;
  $tweets_count_counter = 0;
  for ($i=0; $i < count($hcl_tweets_count); $i++) {
    $tweets_count_counter = $tweets_count_counter + $hcl_tweets_count[$i];
    if ($total_tweets_count < $tweets_count_counter) {
      $video_name = $hcl_tweets_video[$i];
      break;
    }
  }

  if (empty($video_name)) {
    $video_name = $hcl_tweets_video[count($hcl_tweets_video) - 1];
  }

  $video_name = file_load($video_name);
  if (isset($video_name->uri)) {
    $video_name = $video_name->uri;
    $video_name = file_create_url($video_name);
  }

  return $video_name;
}

/**
 * Get video image preview according to tweets count.
 *
 * @param int $total_tweets_count
 *   Total tweets count.
 *
 * @return string
 *   Video image preview uri.
 */
function get_hcl_tweet_image_name($total_tweets_count) {

  global $base_url;

  $hcl_tweets_data = variable_get('hcl_tweets_data', '');

  $hcl_tweets_image = array_values($hcl_tweets_data['hcl_tweets_image_preview']);
  foreach ($hcl_tweets_image as $key => $value) {
    if (empty($value)) {
      $hcl_tweets_image[$key] = isset($hcl_tweets_image[$key - 1]) ? $hcl_tweets_image[$key - 1] : $hcl_tweets_image[$key];
    }
  }
  $hcl_tweets_count = array_values($hcl_tweets_data['hcl_tweets_count']);

  $image_name = 0;
  $tweets_count_counter = 0;
  for ($i=0; $i < count($hcl_tweets_count); $i++) {
    $tweets_count_counter = $tweets_count_counter + $hcl_tweets_count[$i];
    if ($total_tweets_count < $tweets_count_counter) {
      $image_name = $hcl_tweets_image[$i];
      break;
    }
  }

  if (empty($image_name)) {
    $image_name = $hcl_tweets_image[count($hcl_tweets_image) - 1];
  }

  $image_name = file_load($image_name);
  if (isset($image_name->uri)) {
    $image_name = $image_name->uri;
    $image_name = file_create_url($image_name);
  }

  return $image_name;
}

/**
 * Check quiz question is update or not.
 *
 * @param int  $quiz
 *   Nid of quiz.
 *
 * @return bool
 *   If new question is updated then return TRUE else FALSE.
 */
function is_quiz_question_update($quiz) {

  $sql = "select MAX(nid) as nid from node where type='content_type_hcl_campaign_quiz'";
  $conn = db_connection();
  $result = mysql_query($sql, $conn);
  $campaign_quiz_nid = $quiz;
  if (!$result) {
    die('Could not enter data: ' . mysql_error());
  }
  while ($row = mysql_fetch_array($result)) {
    $campaign_quiz_nid = $row{'nid'};
  }

  if ($campaign_quiz_nid > $quiz) {
    $server_name = isset($_SERVER['SERVER_NAME']) ? $_SERVER['SERVER_NAME'] : '';
    $sql = "DELETE from cache_page where cid='http://$server_name/'";
    $conn = db_connection();
    $result = mysql_query($sql, $conn);
    return array(TRUE, $campaign_quiz_nid);
  }

  return array(FALSE, $campaign_quiz_nid);
}
