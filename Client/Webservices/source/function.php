<?php
require_once "config.php";
require_once "string.php";

$conn = mysqli_connect($host, $username, $password) or die ("Not connect server");
mysqli_select_db($conn, $datebase);
mysqli_set_charset($conn, 'utf8');


if (ini_get('date.timezone') != "Asia/Bangkok")
    date_default_timezone_set("Asia/Bangkok");

function checkKey($key)
{
    global $conn;
    $result = mysqli_query($conn, "SELECT COUNT(*) AS TOTAL FROM `privatekey` WHERE `Key` = '" . $key . "';");
    $result = mysqli_fetch_assoc($result);
    if ($result['TOTAL'] > 0)
        return true;
    else return false;
}

//Attendance with RFID send by Post
function attendance($rfid)
{
    global $conn;
    $info = getInfoRFID($rfid);
    while ($info == "Error") {
        $info = getInfoRFID($rfid);
    }
    $event = getEvent();
//    var_dump($info);
    $nowTime = date("H:i:s");
    $result = null;
    $json = array();
    $status = "";
    //kiểm tra ngày hợp lệ
    if (date("Y-m-d") == $event["date"]) {
        //kiểm tra mã RFID đã điểm danh vào cho sự kiện chưa
        if (!isAttendance($rfid, $event['id'])) {
            if ($nowTime < changeTime("-30 minutes", $event['timeStart']) || $nowTime > changeTime("+30 minutes", $event['timeEnd'])) {
                $status = "Time Out";
            } else {
                // Nếu chưa điểm danh thì tiến hành tao thông tin điểm danh
                // Điểm danh vào từ 30 phút trước sự kiên đến 30 trước khi kết thúc sự kiện.
                if ($nowTime >= changeTime("-30 minutes", $event['timeStart']) && $nowTime < changeTime("-30 minutes", $event['timeEnd'])) {
                    $result = mysqli_query($conn, "INSERT INTO `attendance` (`idEvent` ,`idCard` ,`timeIn` ) VALUES ('" . $event['id'] . "','" . $rfid . "','" . $event["date"] . " " . $nowTime . "')");
                    $status = "In";
                } //ngược lại, điểm danh ra cho sự kiện từ khung thời gian từ trước 30 phút kết thúc sự kiện đến 30 sau khi kết thúc sự kiện.
                else if ($nowTime >= changeTime("-30 minutes", $event['timeEnd']) && $nowTime <= changeTime("+30 minutes", $event['timeEnd'])) {
                    $result = mysqli_query($conn, "INSERT INTO `attendance` (`idEvent` ,`idCard` ,`timeOut` ) VALUES ('" . $event['id'] . "','" . $rfid . "','" . $event["date"] . " " . $nowTime . "')");
                    $status = "Out";
                }
            }
        } // Nếu đã điểm danh vào thì tiến hành điểm danh ra.
        else {
            // Kiểm tra điều kiện điểm danh ra.
            if ($nowTime >= changeTime("-30 minutes", $event['timeEnd']) && $nowTime <= changeTime("+30 minutes", $event['timeEnd'])) {
                $result = mysqli_query($conn, "UPDATE `attendance` SET `timeOut` = '" . $event["date"] . " " . $nowTime . "'");
                $status = "Out";
            } else if ($nowTime < changeTime("-30 minutes", $event['timeStart']) || $nowTime > changeTime("+30 minutes", $event['timeEnd'])) {
                $status = "Time Out";
            } else { // Nếu chưa thể điểm danh ra thì thông báo đã điểm danh vào.
                $status = "Attendance";
            }
        }
//        var_dump($info);
        // nếu điểm danh thành công thì thêm thông tin cho json trả về
        if ($result != null || $status == "Attendance" || $status == "Time Out") {
            if ($info['name'] != "New Registry") {
                $json['name'] = utf8ToAscii($info['name']);
                $json['name2'] = $info['name'];
                $json['lastName'] = $info['lastName'];
            } else {
                $json['name'] = $info['id'];
            }
            $json['id'] = $info['id'];
            $json['status'] = $status;
//            $json['time'] = str_replace(":", "", $nowTime);
            $json['time'] =  $nowTime;

            return json_encode($json);
        }
    }

    return "not success.";
}

function getInfoRFID($rfid)
{
    global $conn;
    $result = array();

    $query = mysqli_query($conn, "SELECT * FROM `rfid` WHERE `idCard` = '" . $rfid . "'");
    // Kiểm tra RFID đã đăng ký hay chưa?
//    var_dump($query->num_rows );
    if ($query->num_rows > 0) {
//        var_dump("1");
        $query = mysqli_fetch_assoc($query);
        $istudent = $query['isStudent'];
        $id = $query['personalID'];
        if ($istudent == "1") {
            $row = mysqli_fetch_assoc(mysqli_query($conn, "SELECT `firstNameStudent`,`lastNameStudent` FROM `student` WHERE `StudentID` = '" . $id . "';"));
            $result['name'] = $row['firstNameStudent'];
            $result['lastName'] = $row['lastNameStudent'];
            $result['id'] = $id;
        } else if ($istudent == "0") {
            $row = mysqli_fetch_assoc(mysqli_query($conn, "SELECT `firstNameStaff`, `lastNameStaff` FROM `staff` WHERE `StaffID` = '" . $id . "';"));
            $result['name'] = $row['firstNameStaff'];
            $result['lastName'] = $row['lastNameStaff'];
            $result['id'] = $id;
        } else if ($istudent == "2") {
            $result['name'] = "New Registry";
            $result['id'] = getPersonalId($rfid);
        }
    } // Nếu chưa tiến hành ghi nhận RFID
    else {
//        var_dump("2");
        if (registryRFID($rfid)) {
            $result['name'] = "New Registry";
            $result['id'] = getPersonalId($rfid);
        } else {
            return "Error";
        }
    }
    return $result;
}

function registryRFID($rfid)
{
    global $conn;
    $personalId = "New" . RandomString(7);
    $query = mysqli_query($conn, "INSERT INTO `rfid` (`idCard`, `personalID`, `isStudent`) VALUES ( '" . $rfid . "', '" . $personalId . "', 2) ;");
    return $query != null ? true : false;
}

function getPersonalId($rfid)
{
    global $conn;
    $query = mysqli_query($conn, "SELECT `personalID` FROM `rfid` WHERE `idCard` = '" . $rfid . "';");
    return mysqli_fetch_assoc($query)['personalID'];
}

function getEvent()
{
    global $conn;
    $array = array();
    $result = mysqli_query($conn, "SELECT * FROM `event` JOIN (SELECT `value` FROM `setting` WHERE name = 'event') AS `eventname` ON `event`.`id` = `eventname`.`value`;");

    if ($result != null) {
        $result = mysqli_fetch_assoc($result);

        $array['id'] = $result['id'];
        $array['name'] = $result['nameEvent'];
        $array['timeStart'] = $result['timeStart'];
        $array['timeEnd'] = $result['timeEnd'];
        $array['date'] = $result['dateEvent'];
    }
    return $array;
}

function getEventList()
{
    global $conn;
    $list = array();
    $result = mysqli_query($conn, "SELECT * FROM `event` WHERE `dateEvent` = '" . date("Y-m-d") . "' AND `timeEnd` >= '" . changeTime("-30 minutes", date("H:i:s")) . "' AND `timeStart` <= '" . changeTime("+30 minutes", date("H:i:s")) . "';");

    if (mysqli_num_rows($result) > 0) {
        while ($row = mysqli_fetch_assoc($result)) {
            $array = array();
            $array['id'] = $row['id'];
            $array['name'] = $row['nameEvent'];
            $array['timeStart'] = $row['timeStart'];
            $array['timeEnd'] = $row['timeEnd'];
            $array['date'] = $row['dateEvent'];
            array_push($list, $array);
        }
    }
    return $list;
}

function isAttendance($rfid, $idEvent)
{
    global $conn;
    $result = mysqli_query($conn, "SELECT COUNT(*) AS TOTAL FROM `attendance` WHERE `idCard` = '" . $rfid . "' AND `idEvent`=" . $idEvent . ";");
    $result = mysqli_fetch_assoc($result);
    return ($result['TOTAL'] > 0);
}

function changeTime($change, $time)
{
    return date("H:i:s", strtotime($change, strtotime($time)));
}