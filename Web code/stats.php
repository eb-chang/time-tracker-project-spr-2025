<!DOCTYPE HTML>
<html>
<head>
<link rel="stylesheet" type="text/css" href="./stylesheet.css">
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
</head>

<?php
session_start();
$pageTitle = "Main Menu";
require_once("connect.php");

if ($_SESSION["isAdmin"] != 1) {
    header("Location: main-menu.php");
    exit();
}
$sql = "SELECT id, username FROM user";
$result = $connection->query($sql);

if ($result->num_rows > 0) {
  echo "<table><tr><th>ID</th><th>Name</th></tr>";
  // output data of each row
  while($row = $result->fetch_assoc()) {
    echo "<tr><td>".$row["id"]."</td><td>".$row["username"]." </td></tr>";
  }
  echo "</table>";
} else {
  echo "0 results";
}

?>

<body class="bg">
  <div class="menu-container">
   
  </div>
</body>
</html>