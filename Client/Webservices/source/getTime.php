<?php 
	date_default_timezone_set("asia/bangkok");
	if ($_GET['type']== "date"){
		echo date("d-m-Y");
	}	
	else if ($_GET['type']== "time"){
		echo date("H:i:s");
	}	
?>