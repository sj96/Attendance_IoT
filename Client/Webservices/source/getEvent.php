<?php
require_once "function.php";

if (!empty($_POST['key'])) {
    if (checkKey($_POST['key'])) {
        $json = getEventList();
        echo json_encode($json);
    }
} else echo "Not Access.";
?>