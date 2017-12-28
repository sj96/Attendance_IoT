<?php
/**
 * Created by PhpStorm.
 * User: trana
 * Date: 12/21/2017
 * Time: 7:25 PM
 */

/**
 * Các hàm xử chuỗi
 */


function utf8ToAscii($text)
{
    return utf8tourl(utf8convert($text));
}

function utf8convert($str)
{

    if (!$str) return false;

    $utf8 = array(

        'a' => 'á|à|ả|ã|ạ|ă|ắ|ặ|ằ|ẳ|ẵ|â|ấ|ầ|ẩ|ẫ|ậ',
        'A' => 'Á|À|Ả|Ã|Ạ|Ă|Ắ|Ặ|Ằ|Ẳ|Ẵ|Â|Ấ|Ầ|Ẩ|Ẫ|Ậ',

        'd' => 'đ',
        'D' => 'Đ',

        'e' => 'é|è|ẻ|ẽ|ẹ|ê|ế|ề|ể|ễ|ệ',
        'E' => 'É|È|Ẻ|Ẽ|Ẹ|Ê|Ế|Ề|Ể|Ễ|Ệ',

        'i' => 'í|ì|ỉ|ĩ|ị',
        'I' => 'Í|Ì|Ỉ|Ĩ|Ị',

        'o' => 'ó|ò|ỏ|õ|ọ|ô|ố|ồ|ổ|ỗ|ộ|ơ|ớ|ờ|ở|ỡ|ợ',
        'O' => 'Ó|Ò|Ỏ|Õ|Ọ|Ô|Ố|Ồ|Ổ|Ỗ|Ộ|Ơ|Ớ|Ờ|Ở|Ỡ|Ợ',

        'u' => 'ú|ù|ủ|ũ|ụ|ư|ứ|ừ|ử|ữ|ự',
        'U' => 'Ú|Ù|Ủ|Ũ|Ụ|Ư|Ứ|Ừ|Ử|Ữ|Ự',

        'y' => 'ý|ỳ|ỷ|ỹ|ỵ',
        'Y' => 'Ý|Ỳ|Ỷ|Ỹ|Ỵ',

    );

    foreach ($utf8 as $ascii => $uni) $str = preg_replace("/($uni)/i", $ascii, $str);

    return $str;

}

function utf8tourl($text)
{

    $text = str_replace("ß", "ss", $text);

    $text = str_replace("%", "", $text);

    $text = preg_replace("/[^_a-zA-Z0-9 -] /", "", $text);

    $text = str_replace(array('%20', ' '), '-', $text);

    $text = str_replace("----", "-", $text);

    $text = str_replace("---", "-", $text);

    $text = str_replace("--", "-", $text);

    return $text;

}

//Sinh mã ngẫu nhiên độ dài chuỗi mặt định 10
function RandomString($length = 10) {
    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < $length; $i++) {
        $randomString .= $characters[rand(0, $charactersLength - 1)];
    }
    return $randomString;
}