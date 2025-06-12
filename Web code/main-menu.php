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

?>
<script type="text/javascript">document.getElementById("stats-button").style.display="block";</script>

<body class="bg">
  <div class="menu-container">
    <h1 class="menu-title">time tracker</h1>
    <a class="darkbutton" href="timer.html">standard timer</a>
    <a class="darkbutton" id="stats-button" href="stats.php">statistics</a>
    <form method="POST" action="log-out.php">
      <input type="submit" id="submit" class="lightbutton" value="log out">
    </form>
  </div>
</body>

</html>
