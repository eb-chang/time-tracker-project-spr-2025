<?php
$pageTitle = "Sign Up";
session_start();
require_once("connect.php");

//regex
$unameRegex = '/^[a-zA-Z0-9._-]{3,15}$/';
$passRegex = '/^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[a-zA-Z]).{8,15}$/';

// insert
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $username = $_POST["username"];
    $password = $_POST["password"];
    if (preg_match($unameRegex, $username) == 1) {
        if (preg_match($passRegex, $password) == 1) {
            $sql = "INSERT INTO user (`username`, `password`, `isAdmin`)
            VALUES ('$username', '$password', 0)";

            if (mysqli_query($connection, $sql)) {
                echo "New record created successfully";
            } else {
                echo "Error: " . $sql . "<br>" . mysqli_error($connection);
            }
            // login successful, head to main menu.
            $_SESSION["username"] = $row["username"];
            $_SESSION["login"] = true;
            $_SESSION["isAdmin"] = $row["isAdmin"]; // Store admin status
            $_SESSION["password"] = $row["password"];
            header("Location: main-menu.php");
        }
    } else {
        // password regex mismatch
        SignupDisplay();
        echo '<script>alert("Password must be 8-15 characters long, include a capital letter, and include at least one number.")</script>';
    }
    // username regex mismatch
    SignupDisplay();
    echo '<script>alert("Username must be 3-15 characters long. Can include letters, numbers, periods, underscores, and dashes.")</script>';
} else {
  //  SignupDisplay();
}


function SignupDisplay()
{
    echo '<body class="bg">
  <div class="menu-container">
    <h1 class="menu-title">sign up</h1>
    
    <form action="sign-up2.php" method="POST">
        <input type="text" class="login-text vertical" id="username" placeholder="username" name = "username" required>
        <p for="username" class="description-text">3 &dash; 15 characters, letters, numbers, ., _, or -</p>
        <input type="password" class="login-text vertical" id="password" placeholder="password" name = "password" required>
        <p for="password" class="description-text">8 &dash; 15 characters long, include a capital letter and a number.</p>
        <input type="submit" id="submit" class="darkbutton" value="sign up">
        
    </form>
    <a href="start.html" class = "lightbutton vertical">back</a>
  </div>
</body>';
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