<?php
$link = mysql_connect('localhost','root', '');
if (!$link) {
	die ('Non riesco a connettermi: ' . mysql_error());
}



$db_selected = mysql_select_db('dati',$link);
if (!$db_selected) {
	die ("Errore nella selezione del database: " . mysql_error());
}
?>
