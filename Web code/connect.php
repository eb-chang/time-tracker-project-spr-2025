<?php
//login
// all the files i require this have these constants
define("DB_IP", "localhost");
define("DB_USER", "root");
define("DB_PASS", "");
define("DB_DB", "timer_db");

$connection = new mysqli(DB_IP, DB_USER, DB_PASS, DB_DB);

// Check for a connection error:
if ($connection->connect_error) {
    die('Could not connect to MySQL: ' . $connection->connect_error);
} 

// Set the encoding to UTF-8
$connection->set_charset('utf8');

?>