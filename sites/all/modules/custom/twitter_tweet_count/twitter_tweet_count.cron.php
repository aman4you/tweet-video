<?php
/**
 * @file
 * Twitter tweet count module file.
 */

include_once 'lib.php';

hash_tag_tweet_count();

function hash_tag_tweet_count() {
  $hash_tag = variable_get('hcl_campaign_hashtag', '#hcl');
  $tweet_count = get_tweets($hash_tag);
}

function get_tweets($hash_tag) {
  $base_path = base_path;

  $twitteroauth_lib_path = libraries_get_path('TwitterOAuth');
  $twitteroauth_lib_file = $twitteroauth_lib_path . '/twitteroauth.php';
  include "$base_path/" . $twitteroauth_lib_file;

  $twitter_customer_key        = variable_get('hcl_campaign_twitter_customer_key', '');
  $twitter_customer_secret     = variable_get('hcl_campaign_twitter_customer_secret', '');
  $twitter_access_token        = variable_get('hcl_campaign_twitter_access_token', '');
  $twitter_access_token_secret = variable_get('hcl_campaign_twitter_access_token_secret', '');

  $query_result_count = 100;

  $connection = new TwitterOAuth($twitter_customer_key, $twitter_customer_secret, $twitter_access_token, $twitter_access_token_secret);

  $tweets_count = $total_tweets_count = 0;
  $hcl_tweets_since_id = variable_get('hcl_tweets_since_id', NULL);

  $tweets_parameter = array(
    'q' => $hash_tag,
    'count' => $query_result_count,
    'include_entities' => TRUE,
  );

  if (isset($hcl_tweets_since_id)) {
    $tweets_parameter['since_id'] = $hcl_tweets_since_id;
  }

  // Send query to twitter server to fetch tweets.
  $tweets = $connection->get('search/tweets', $tweets_parameter);

  if (isset($tweets->statuses[0]->id_str)) {
    $since_id = $tweets->statuses[0]->id_str;
    variable_set('hcl_tweets_since_id', $since_id);
  }

  $tweets_count = isset($tweets->statuses) ? count($tweets->statuses) : $tweets_count;
  $total_tweets_count = variable_get('hcl_tweets_total_count', 0);
  $total_tweets_count = $total_tweets_count + $tweets_count;
  variable_set('hcl_tweets_total_count', $total_tweets_count);

  return $total_tweets_count;
}

function libraries_get_path($librarie_name) {
  return 'sites/all/libraries/' . $librarie_name;
}
