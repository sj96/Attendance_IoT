<?php
require_once "function.php";


//$rfid = "5493812";
//echo attendance($rfid);

if (!empty($_POST['key'])){
	if(checkKey($_POST['key'])){
		echo attendance($_POST['rfid']);
	}
}
else echo "Not Access.";
?>
