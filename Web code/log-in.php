<?php
session_start();
$pageTitle = "Log In";
require_once("connect.php");

function LoginForm() {
    echo '<body class="bg">
  <div class="menu-container">
    <h1 class="menu-title">log in</h1>
    <form action="log-in.php" method="POST">
        <input type="text" name="username" class="login-text vertical" id="username" placeholder="username" required>
        <input type="password" name="password" class="login-text vertical" id="password" placeholder="password" required>
        <!--<input type="checkbox" id="remember" class="" name="remember" >Remember me -->
        <input type="submit" id="submit" class="darkbutton" value="log in">
    </form>
    <a href="start.html" class = "lightbutton vertical">back</a>
  </div>
</body>
';  
}

// regex
$unameRegex = '/^[a-zA-Z0-9._-]{3,15}$/';
$passRegex = '/^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[a-zA-Z]).{8,15}$/';

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $username = $_POST["username"];
    $password = $_POST["password"];

    // Validate input
    if (!preg_match($unameRegex, $username)) {
        echo "<span class='error'>*Invalid username: must be 3-15 characters (letters, numbers, ., _, -)</span><br>";
        LoginForm();
        exit();
    }

    //Skip Password regex check for known admin override
    if ($username !== 'isAdmin' && !preg_match($passRegex, $password)) {
        echo "<span class='error'>*Invalid password: 8-15 chars, 1 uppercase, 1 number</span><br>";
        LoginForm();
        exit();
    }

    // Check user in DB
    $sql = "SELECT * FROM user WHERE username='$username' AND password='$password'";
    $result = $connection->query($sql);

    if ($result && $result->num_rows === 1) {
        $row = $result->fetch_assoc();
        $_SESSION["uname"] = $username;
        $_SESSION["login"] = true;
        $_SESSION["isAdmin"] = $row["isAdmin"]; // Store admin status
        $_SESSION["userID"] = $row["id"];

        //echo $_SESSION["isAdmin"];
        header("Location: main-menu.php");
        exit();
    } else {
        echo '<script>alert("Invalid Login.")</script>';
        $_SESSION["login"] = false;
        LoginForm();
        exit();
    }
}

// If not logged in yet
if (!isset($_SESSION["login"]) || $_SESSION["login"] !== true) {
    LoginForm();
} else {
    echo "<p>Welcome back, " . htmlspecialchars($_SESSION["uname"]) . "!</p>";
}
?>

<html>
<header>
    <link rel="stylesheet" type="text/css" href="./stylesheet.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
</header>

</html>