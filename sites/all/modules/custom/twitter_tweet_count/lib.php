<?php

define('base_path', '/var/www/tweet-video');

/**
 * Connect with database.
 *
 * @return string
 *   Connection id.
 */
function db_connection() {
  $base_path = base_path;
  include "$base_path/sites/default/settings.php";

  $database = $databases['default']['default']['database'];
  $username = $databases['default']['default']['username'];
  $password = $databases['default']['default']['password'];
  $host     = isset($databases['default']['default']['host']) ? $databases['default']['default']['host'] : 'localhost';

  $dbhost = $host;
  $dbuser = $username;
  $dbpass = $password;
  $conn = mysql_connect($dbhost, $dbuser, $dbpass);
  mysql_select_db($database, $conn);

  return $conn;
}

/**
 * Load a file from file id.
 *
 * @param int $fid
 *   File id.
 *
 * @return object
 *   Details of file.
 */
function file_load($fid) {
  $sql = "select * from file_managed where fid='$fid'";
  $conn = db_connection();
  $result = mysql_query($sql, $conn);
  if(!$result){
    die('Could not enter data: ' . mysql_error());
  }
  while ($row = mysql_fetch_array($result)) {
    $value['fid'] = $row['fid'];
    $value['uri'] = $row{'uri'};
    $value['status'] = $row{'status'};
  }

  if (!isset($value)) {
    $value = array();
  }

  $value = (object) $value;

  return $value;
}

/**
 * Get stored value from database.
 *
 * @param string $name
 *   Variable value.
 * @param string $default
 *   Default Variable value.
 *
 * @return string
 *   Value from database.
 */
function variable_get($name, $default) {
  $sql = "select * from variable where name='$name'";
  $conn = db_connection();
  $result = mysql_query($sql, $conn);
  if (!$result) {
    die('Could not enter data: ' . mysql_error());
  }
  while ($row = mysql_fetch_array($result)) {
    $value = unserialize($row{'value'});
  }

  if (!isset($value)) {
    $value = $default;
  }

  return $value;
}

/**
 * Create a file.
 *
 * @param int $file
 *   Fid of file.
 *
 * @return string
 *   File name.
 */
function file_create_url($file) {
  $file = str_replace('public://', 'sites/default/files/', $file);
  $file = str_replace('//', '/', $file);
  $protocol = 'http://';
  $server_name = isset($_SERVER['SERVER_NAME']) ? $_SERVER['SERVER_NAME'] : '';
  $file = $protocol . '' . $server_name . '/' . $file;

  return $file;
}

/**
 * Set a variable in database.
 *
 * @param string $name
 *   Name of the variable.
 * @param string $value
 *   Value of the variable.
 *
 * @return bool
 *   On success return TRUE else FALSE.
 */
function variable_set($name, $value) {
  $value = serialize($value);
  $sql = "select * from variable where name='$name'";
  $conn = db_connection();
  $result = mysql_query($sql, $conn);

  // Check variable is exist or not in database.
  $data = FALSE;
  while ($row = mysql_fetch_array($result)) {
    $data = TRUE;
    break;
  }

  $sql = $data ? "UPDATE variable SET value = '$value' where name = '$name'" : "INSERT INTO variable (name, value) VALUES ('$name', '$value')";
  $result = mysql_query($sql, $conn);

  mysql_close($conn);
  return $result;
}
