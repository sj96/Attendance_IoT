-- phpMyAdmin SQL Dump
-- version 4.0.4.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Dec 26, 2017 at 04:57 AM
-- Server version: 5.6.13
-- PHP Version: 5.4.17

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `diemdanh_nckh_webservices`
--
CREATE DATABASE IF NOT EXISTS `diemdanh_nckh_webservices` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `diemdanh_nckh_webservices`;

-- --------------------------------------------------------

--
-- Table structure for table `account`
--

CREATE TABLE IF NOT EXISTS `account` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `username` char(255) COLLATE utf8_unicode_ci NOT NULL,
  `password` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `email` char(75) COLLATE utf8_unicode_ci DEFAULT NULL,
  `name` char(128) COLLATE utf8_unicode_ci DEFAULT NULL,
  `rolename` char(20) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'user',
  PRIMARY KEY (`id`,`username`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=8 ;

--
-- Dumping data for table `account`
--

INSERT INTO `account` (`id`, `username`, `password`, `email`, `name`, `rolename`) VALUES
(1, 'admin', '1234', 'admin@ctu.edu.vn', 'Quản trị viên', 'admin'),
(2, 'ntduy', '1234', 'ntduy@ctu.edu.vn', 'Nguyễn Thanh Duy', 'manager'),
(3, 'phuocthanh', '1234', 'phuocthanh@ctu.edu.vn', 'Lâm Phước Thành', 'manager'),
(4, 'hploc', '1234', 'hploc@ctu.edu.vn', 'Huỳnh Phúc Lộc', 'admin'),
(5, 'quanbao', '1234', 'baob1507712@ctu.edu.vn', 'Trương Quân Bảo', 'user'),
(6, 'ngthuc', '1234', 'thucb1400731@student.ctu.edu.vn', 'Lê Nguyên Thức', 'user'),
(7, 'ngochuy', '1234', 'huyb1507332@student.ctu.edu.vn', 'Trần Ngọc Huy', 'user');

-- --------------------------------------------------------

--
-- Table structure for table `attendance`
--

CREATE TABLE IF NOT EXISTS `attendance` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `idEvent` int(20) NOT NULL,
  `idCard` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `timeIn` datetime DEFAULT NULL,
  `timeOut` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `attendance` (`idEvent`),
  KEY `attendancerfid` (`idCard`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=5 ;

-- --------------------------------------------------------

--
-- Table structure for table `department`
--

CREATE TABLE IF NOT EXISTS `department` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `nameDepartment` varchar(128) COLLATE utf8_unicode_ci NOT NULL,
  `idFaculty` char(10) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=15 ;

--
-- Dumping data for table `department`
--

INSERT INTO `department` (`id`, `nameDepartment`, `idFaculty`) VALUES
(6, 'Công nghệ phần mềm', 'DI'),
(7, 'Mạng máy tính và truyền thông', 'DI'),
(8, 'Công nghệ thông tin', 'DI'),
(9, 'Hệ thống thông tin', 'DI'),
(10, 'Khoa học máy tính', 'DI'),
(11, 'Tin học ứng dụng', 'DI'),
(12, 'Ban giám hiệu - Trường Đại học Cần Thơ', NULL),
(13, 'Phòng Hợp tác Quốc tế - Trường Đại học Cần Thơ', NULL),
(14, 'Văn phòng Đoàn Hội - Trường Đại học Cần Thơ', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `devices`
--

CREATE TABLE IF NOT EXISTS `devices` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `serialnumber` char(50) DEFAULT NULL,
  `registerdate` date NOT NULL,
  `idApi` int(5) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `devices`
--

INSERT INTO `devices` (`id`, `name`, `serialnumber`, `registerdate`, `idApi`) VALUES
(1, 'TNTN_M_001', '25852085245SNL', '2017-12-21', 1),
(2, 'TNTN_M_002', '25852085245SNL', '2017-12-21', 2),
(3, 'TNTN_M_003', '25852085245SNL', '2017-12-21', 3),
(4, 'TNTN_M_004', '25852085245SNL', '2017-12-21', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `event`
--

CREATE TABLE IF NOT EXISTS `event` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `nameEvent` varchar(256) COLLATE utf8_unicode_ci NOT NULL,
  `timeStart` time NOT NULL,
  `timeEnd` time NOT NULL,
  `dateEvent` date NOT NULL,
  `locationEvent` varchar(128) COLLATE utf8_unicode_ci NOT NULL,
  `descriptionEvent` varchar(256) COLLATE utf8_unicode_ci DEFAULT NULL,
  `userCreator` char(255) COLLATE utf8_unicode_ci NOT NULL,
  `idOrg` int(5) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=9 ;

--
-- Dumping data for table `event`
--

INSERT INTO `event` (`id`, `nameEvent`, `timeStart`, `timeEnd`, `dateEvent`, `locationEvent`, `descriptionEvent`, `userCreator`, `idOrg`) VALUES
(1, 'Khám phá tri thức CNTT 2017 - Buổi 1', '07:30:00', '12:00:00', '2017-12-26', 'Hội trường lớn', 'Tuần lễ Khám phá tri thức CNTT năm 2017', 'admin', 4),
(2, 'Khám phá tri thức CNTT 2017 - Buổi 2', '14:30:00', '16:30:00', '2017-12-07', 'Hội trường 2, khoa CNTT&TT', 'Tuần lễ Khám phá tri thức CNTT năm 2017', 'admin', 4),
(3, 'Khám phá tri thức CNTT 2017 - Buổi 3', '07:30:00', '10:30:00', '2017-12-08', 'Hội trường 2, khoa CNTT&TT', 'Tuần lễ Khám phá tri thức CNTT năm 2017', 'admin', 4),
(4, 'Khám phá tri thức CNTT 2017 - Buổi 4', '14:30:00', '16:30:00', '2017-12-08', 'Hội trường 2, khoa CNTT&TT', 'Tuần lễ Khám phá tri thức CNTT năm 2017', 'admin', 4),
(5, 'Test1', '08:00:00', '11:00:00', '2017-12-23', 'Hội trường 2 - khoa CNTT&TT', 'Thử nghiệm', 'admin', 4),
(6, 'Test2', '15:35:00', '23:00:00', '2017-12-23', 'Hội trường 2 - khoa CNTT&TT', 'Thử nghiệm', 'admin', 4),
(7, 'Test3', '22:30:00', '23:00:00', '2017-12-23', 'Hội trường 2 - khoa CNTT&TT', 'Thử nghiệm', 'admin', 4),
(8, 'Test4', '22:00:00', '23:00:00', '2017-12-21', 'Hội trường 2 - khoa CNTT&TT', 'Thử nghiệm', 'admin', 4);

-- --------------------------------------------------------

--
-- Table structure for table `faculty`
--

CREATE TABLE IF NOT EXISTS `faculty` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `idFaculty` char(10) NOT NULL,
  `nameFaculty` varchar(128) NOT NULL,
  PRIMARY KEY (`id`,`idFaculty`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=18 ;

--
-- Dumping data for table `faculty`
--

INSERT INTO `faculty` (`id`, `idFaculty`, `nameFaculty`) VALUES
(1, 'DI', 'Công nghệ thông tin & Truyền thông'),
(2, 'KL', 'Luật'),
(3, 'CN', 'Công nghệ'),
(4, 'TN', 'Khoa học Tự nhiên'),
(5, 'XH', 'Khoa học Xã hội & Nhân văn'),
(6, 'FL', 'Ngoại ngữ'),
(7, 'DB', 'Dự bị Dân tộc'),
(8, 'NN', 'Nông nghiệp & Sinh học Ứng dụng'),
(9, 'MT', 'Môi trường & Tài nguyên Thiên nhiên'),
(10, 'ML', 'Khoa học Chính trị'),
(11, 'KT', 'Kinh tế'),
(12, 'TC', 'Giáo dục Thể chất'),
(13, 'SP', 'Sư phạm'),
(14, 'HG', 'Phát triển Nông thôn'),
(15, 'CS', 'Nghiên cứu & Phát triển Công nghệ Sinh học'),
(16, 'PD', 'Nghiên cứu & Phát triển Đồng bằng Sông Cửu Long'),
(17, 'TS', 'Thủy sản');

-- --------------------------------------------------------

--
-- Table structure for table `major`
--

CREATE TABLE IF NOT EXISTS `major` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `idMajor` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `nameMajor` varchar(128) COLLATE utf8_unicode_ci NOT NULL,
  `idFaculty` char(10) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`,`idMajor`),
  KEY `idMajor` (`idMajor`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=7 ;

--
-- Dumping data for table `major`
--

INSERT INTO `major` (`id`, `idMajor`, `nameMajor`, `idFaculty`) VALUES
(1, '96', 'Kỹ thuật phần mềm', 'DI'),
(2, 'V7', 'Công nghệ thông tin', 'DI'),
(3, 'Y1', 'Tin học ứng dụng', 'DI'),
(4, 'Y9', 'Truyền thông và mạng máy tính', 'DI'),
(5, 'Z6', 'Khoa học máy tính', 'DI'),
(6, '95', 'Hệ thống thông tin', 'DI');

-- --------------------------------------------------------

--
-- Table structure for table `organizations`
--

CREATE TABLE IF NOT EXISTS `organizations` (
  `id` int(5) NOT NULL,
  `parent` int(5) NOT NULL DEFAULT '0',
  `text` varchar(255) NOT NULL,
  `description` char(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `organizations`
--

INSERT INTO `organizations` (`id`, `parent`, `text`, `description`) VALUES
(1, 1, 'Trường Đại học Cần Thơ', 'Trường Đại học vùng trọng điểm Quốc gia'),
(2, 2, 'Đoàn trường Đại học Cần Thơ', 'Đoàn tương đương cấp Quận/Huyện'),
(3, 3, 'Hội Sinh viên trường Đại học Cần Thơ', 'Trực thuộc Hội Sinh viên Thành phố Cần Thơ'),
(4, 2, 'Đoàn khoa CNTT&TT', 'Đoàn cơ sở trực thuộc Đoàn trường Đại học Cần Thơ'),
(5, 3, 'Liên Chi hội Sinh viên Cần Thơ', 'Liên Chi hội theo tỉnh thành trực thuộc Hội sinh viên trường Đại học Cần Thơ'),
(6, 1, 'Trung tâm Học liệu', 'Thư viện học liệu, trung tâm trực thuộc trường Đại học Cần Thơ'),
(7, 4, 'CLB Tin học', 'CLB học thuật trực thuộc Đoàn khoa CNTT&TT'),
(8, 4, 'Đội Thanh niên Tình nguyện', 'Lực lượng sinh viên tình nguyện trực thuộc Đoàn khoa CNTT&TT');

-- --------------------------------------------------------

--
-- Table structure for table `privatekey`
--

CREATE TABLE IF NOT EXISTS `privatekey` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `Key` varchar(256) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=2 ;

--
-- Dumping data for table `privatekey`
--

INSERT INTO `privatekey` (`id`, `Key`) VALUES
(1, 'b091f0444231106d8e7b796ae7508bb50fc9c17556118fe705266018a4173438');

-- --------------------------------------------------------

--
-- Table structure for table `register`
--

CREATE TABLE IF NOT EXISTS `register` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `personalID` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `idEvent` int(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `register` (`idEvent`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `rfid`
--

CREATE TABLE IF NOT EXISTS `rfid` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `idCard` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `personalID` char(10) COLLATE utf8_unicode_ci DEFAULT NULL,
  `isStudent` int(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`idCard`),
  KEY `idCard` (`idCard`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=16 ;

--
-- Dumping data for table `rfid`
--

INSERT INTO `rfid` (`id`, `idCard`, `personalID`, `isStudent`) VALUES
(2, '0770056810', '002356', 0),
(3, '0101503659', '002321', 0),
(4, '0770236810', '001232', 0),
(5, '0770056910', '002354', 0),
(6, '0770055520', '001234', 0),
(7, '0770235210', 'B1400731', 1),
(8, '0785256810', 'B1400706', 1),
(9, '0780056810', 'B1400729', 1),
(10, '0790056810', 'B1608553', 1),
(11, '0770056810', 'B1400704', 1);

-- --------------------------------------------------------

--
-- Table structure for table `roles`
--

CREATE TABLE IF NOT EXISTS `roles` (
  `idRole` int(12) NOT NULL AUTO_INCREMENT,
  `roleName` varchar(255) NOT NULL,
  `rolesGroup` longtext NOT NULL,
  `roleDesc` varchar(255) CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`idRole`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `roles`
--

INSERT INTO `roles` (`idRole`, `roleName`, `rolesGroup`, `roleDesc`) VALUES
(1, 'Owner', 'fullcontrol,device,borrowDevice,members,project,labs,profile,search,dashboard,account,mailCP,urlCP,addDevice,removeDevice,addMember,removeMember,addProject,removeProject,addLabs,removeLab,addPartner,removePartner,deviceCP,borrowDeviceCP,membersCP,projectCP,labsCP,producerCP,imagesCP,rolesCP,profileCP,rolesAD,settingCP', 'Tất cả quyền'),
(2, 'Admin', 'device,borrowDevice,members,project,labs,profile,search,dashboard,addDevice,removeDevice,addMember,removeMember,addProject,removeProject,addLabs,removeLab,addPartner,removePartner,deviceCP,borrowDeviceCP,membersCP,projectCP,labsCP,producerCP,imagesCP,rolesCP,profileCP', 'Tất cả quyền (trừ quyền cài đặt và quản lý nhóm quyền)'),
(3, 'User', 'device,borrowDevice,members,project,labs,profile,search', 'Chỉ nhóm quyền xem và không truy cập AdminCP'),
(4, 'Manager', 'device,borrowDevice,members,project,labs,profile,search,dashboard,addDevice,addMember,addProject,addLabs,addPartner,deviceCP,borrowDeviceCP,membersCP,projectCP,labsCP,producerCP', 'Nhóm quyền xem, quyền quản lý cơ bản'),
(6, 'Deny', 'profile', 'Bị cấm toàn hệ thống');

-- --------------------------------------------------------

--
-- Table structure for table `setting`
--

CREATE TABLE IF NOT EXISTS `setting` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `value` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=2 ;

--
-- Dumping data for table `setting`
--

INSERT INTO `setting` (`id`, `name`, `value`) VALUES
(1, 'Event', '1');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE IF NOT EXISTS `staff` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `staffID` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `firstNameStaff` varchar(256) COLLATE utf8_unicode_ci NOT NULL,
  `lastNameStaff` varchar(256) COLLATE utf8_unicode_ci NOT NULL,
  `idDepartment` int(5) DEFAULT NULL,
  PRIMARY KEY (`id`,`staffID`),
  KEY `staffdepartment` (`idDepartment`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=7 ;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`id`, `staffID`, `firstNameStaff`, `lastNameStaff`, `idDepartment`) VALUES
(2, '002356', 'Cao Đệ', 'Trần', 8),
(3, '002321', 'Bá Hùng', 'Ngô', 7),
(4, '001232', 'Phương Lan', 'Phan', 6),
(5, '002354', 'Minh Thái', 'Trương', 6),
(6, '001234', 'Huỳnh Trâm', 'Võ', 6);

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE IF NOT EXISTS `student` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `studentID` char(10) COLLATE utf8_unicode_ci NOT NULL,
  `firstNameStudent` varchar(256) COLLATE utf8_unicode_ci NOT NULL,
  `lastNameStudent` varchar(256) COLLATE utf8_unicode_ci NOT NULL,
  `idMajor` char(10) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`,`studentID`),
  KEY `studentmajor` (`idMajor`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`id`, `studentID`, `firstNameStudent`, `lastNameStudent`, `idMajor`) VALUES
(1, 'B1400731', 'Nguyên Thức', 'Lê', '96'),
(2, 'B1400704', 'Minh Luân', 'Lê', '96'),
(3, 'B1400706', 'Thiện Minh', 'Nguyễn', '96'),
(4, 'B1400729', 'Hoàng Thơ', 'Huỳnh', '96'),
(5, 'B1608553', 'Bửu Minh', 'Phương', 'V7');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `attendance`
--
ALTER TABLE `attendance`
  ADD CONSTRAINT `attendance_ibfk_1` FOREIGN KEY (`idCard`) REFERENCES `rfid` (`idCard`) ON DELETE CASCADE,
  ADD CONSTRAINT `attendance_ibfk_2` FOREIGN KEY (`idEvent`) REFERENCES `event` (`id`) ON DELETE CASCADE;

--
-- Constraints for table `register`
--
ALTER TABLE `register`
  ADD CONSTRAINT `register_ibfk_1` FOREIGN KEY (`idEvent`) REFERENCES `event` (`id`) ON DELETE CASCADE;

--
-- Constraints for table `staff`
--
ALTER TABLE `staff`
  ADD CONSTRAINT `staffdepartment` FOREIGN KEY (`idDepartment`) REFERENCES `department` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `student`
--
ALTER TABLE `student`
  ADD CONSTRAINT `student_ibfk_1` FOREIGN KEY (`idMajor`) REFERENCES `major` (`idMajor`) ON DELETE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
