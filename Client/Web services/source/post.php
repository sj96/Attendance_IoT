<?php
/**
 * Created by PhpStorm.
 * User: trana
 * Date: 12/27/2017
 * Time: 4:30 AM
 */

require_once "function.php";

if (!empty($_POST['APIkey'])) {
    if ($_POST['APIkey']== "6a22a56f3a8c03f3774ec99edfb35c39") {
        $json = $_POST['data'];
        print_r( $json);
    }
} else echo "Not Access.";