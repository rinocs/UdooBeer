

<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "dati";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// sql to create table
$sql = "CREATE TABLE IF NOT EXISTS udoo_dati (
id INT(11) NOT NULL AUtO_INCREMENT PRIMARY KEY,
Temperature VARCHAR(5) NOT NULL ,
Alcohol VARCHAR(5) NOT NULL,
Pressure VARCHAR(25) NOT NULL,
Hour VARCHAR(5) NOT NULL,
Minute VARCHAR(5) NOT NULL,
Second VARCHAR(5) NOT NULL,
Data VARCHAR(15) NOT NULL
)";

if ($conn->query($sql) === TRUE) {
    
} else {
    echo "Error creating table: " . $conn->error;
}

$conn->close();
?>
