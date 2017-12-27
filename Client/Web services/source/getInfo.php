<?php
/**
 * Created by PhpStorm.
 * User: trana
 * Date: 12/21/2017
 * Time: 1:48 AM
 */

require_once "function.php";

if (!empty($_POST["key"])) {
    if (checkKey($_POST["key"])) {
        date_default_timezone_set("Asia/Bangkok");

        $json = array();

        $event = getEvent();
        if (!empty($event)) {
            $json["event"] = utf8ToAscii($event["name"]);
            $json['id'] = $event['id'];
            $json['timeStart'] = $event['timeStart'];
            $json['timeEnd'] = $event['timeEnd'];
        } else{
            $json["event"] = "No Event";
            $json['id'] = "";
            $json['timeStart'] = "";
            $json['timeEnd'] = "";
        }

        $json["date"] = date("d-m-Y");
        $json["date2"] = date("dmY");

        echo json_encode($json);
    }
} else echo "Not Access.";