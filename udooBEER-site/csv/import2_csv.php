<?php
include ("connect.php");
// specify connection info
function csv_import(){

/*
$connect = mysql_connect('localhost','root','');
if (!$connect)
{
   die('Could not <span id="IL_AD1" class="IL_AD">
    connect to</span> MySQL: ' . mysql_error());
}

$cid =mysql_select_db('dati',$connect); //specify db name*/

$delete_sql= " DELETE FROM udoo_dati ";
$rdelete_sql=mysql_query($delete_sql) or die ("Errore nell'esecuzione della query: " . mysql_error());

$auto_sql = "ALTER TABLE udoo_dati  AUTO_INCREMENT = 1 ";
mysql_query($auto_sql );



define('CSV_PATH','/var/www/udooBEER/csv/'); // specify CSV file path
$today = date("d-m-Y");

$file_Name=$today.".csv";


$csv_file = CSV_PATH.$file_Name; // Name of your CSV file

$csvfile = fopen($csv_file, 'r');
$theData = fgets($csvfile);
$i=0;
while (!feof($csvfile))
{
   $csv_data[] = fgets($csvfile, 1024);
   $csv_array = explode(",", $csv_data[$i]);
   $insert_csv = array();
   $insert_csv['Temperature'] = $csv_array[0];
   $insert_csv['Alcohol'] = $csv_array[1];
   $insert_csv['Pressure'] = $csv_array[2];
   $insert_csv['Hour'] = $csv_array[3];
   $insert_csv['Minute'] = $csv_array[4];
   $insert_csv['Second'] = $csv_array[5];
   $insert_csv['Data'] = $csv_array[6];



  $query = "INSERT INTO udoo_dati(Temperature,Alcohol,Pressure,Hour,Minute,Second,Data)
     VALUES('".$insert_csv['Temperature']."','".$insert_csv['Alcohol']."','". $insert_csv['Pressure']."','".$insert_csv['Hour']."','".$insert_csv['Minute']."','". $insert_csv['Second']."','". $insert_csv['Data']."')";
   $n=mysql_query($query);
   $i++;
}


// devo salvare i e passarlo
fclose($csvfile);



}


?>
