-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: localhost    Database: education_system
-- ------------------------------------------------------
-- Server version	8.0.28

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `admin` (
  `a_id` varchar(15) NOT NULL,
  `a_name` varchar(20) DEFAULT NULL,
  `a_password` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`a_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin`
--

LOCK TABLES `admin` WRITE;
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` VALUES ('0','王语文','123456'),('1810300215','邓兆阳','123456');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `course` (
  `c_id` varchar(15) NOT NULL,
  `c_name` varchar(20) DEFAULT NULL,
  `c_teacher_id` varchar(15) DEFAULT NULL,
  `c_class` varchar(10) DEFAULT NULL,
  `c_time_day` varchar(5) DEFAULT NULL,
  `c_time` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`c_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('1','语文','0','3','1','1'),('10','语文','0','3','2','3'),('11','数学','1','3','2','4'),('12','英语','2','3','2','5'),('13','政治','3','3','2','6'),('14','历史','4','3','2','7'),('15','地理','5','3','3','1'),('16','物理','6','3','3','2'),('17','化学','7','3','3','3'),('18','生物','8','3','3','4'),('19','语文','0','3','3','5'),('2','数学','1','3','1','2'),('20','数学','1','3','3','6'),('21','英语','2','3','3','7'),('22','政治','3','3','4','1'),('23','历史','4','3','4','2'),('24','地理','5','3','4','3'),('25','物理','6','3','4','4'),('26','化学','7','3','4','5'),('27','生物','8','3','4','6'),('28','语文','0','3','4','7'),('29','数学','1','3','5','1'),('3','英语','2','3','1','3'),('30','英语','2','3','5','2'),('31','政治','3','3','5','3'),('32','历史','4','3','5','4'),('33','地理','5','3','5','5'),('34','物理','6','3','5','6'),('35','化学','7','3','5','7'),('36','语文','0','2','2','1'),('4','政治','3','3','1','4'),('5','历史','4','3','1','5'),('6','地理','5','3','1','6'),('7','物理','6','3','1','7'),('8','化学','7','3','2','1'),('9','生物','8','3','2','2');
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `score`
--

DROP TABLE IF EXISTS `score`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `score` (
  `sc_id` varchar(15) NOT NULL,
  `sc_s_id` varchar(10) NOT NULL,
  `sc_t_id` varchar(5) NOT NULL,
  `sc_score` double DEFAULT NULL,
  PRIMARY KEY (`sc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `score`
--

LOCK TABLES `score` WRITE;
/*!40000 ALTER TABLE `score` DISABLE KEYS */;
INSERT INTO `score` VALUES ('1','1810300215','0',1),('11','1810300216','0',NULL),('12','1810300217','0',NULL),('2','1810300215','1',80),('3','1810300215','2',82),('4','1810300215','3',83),('5','1810300215','4',84),('6','1810300215','5',85),('7','1810300215','6',NULL),('8','1810300215','7',NULL),('9','1810300215','8',NULL);
/*!40000 ALTER TABLE `score` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `s_id` varchar(10) NOT NULL,
  `s_name` varchar(20) DEFAULT NULL,
  `s_age` varchar(3) DEFAULT NULL,
  `s_sex` varchar(1) DEFAULT NULL,
  `s_grade` varchar(10) DEFAULT NULL,
  `s_class` varchar(10) DEFAULT NULL,
  `s_tel` varchar(11) DEFAULT NULL,
  `s_password` varchar(20) DEFAULT NULL,
  `s_img` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`s_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('1810300215','邓兆阳','22','男','22','3','13997552490','123456','1.jpeg'),('1810300216','邓兆兆','22','男','18','3','13997552490','123456',NULL),('1810300217','邓阳阳','22','男','18','2','13997552490','123456',NULL),('1900001','罗霞','20','女',NULL,NULL,'63078225','awfox',NULL),('3400001','方强','21','女',NULL,NULL,'86910486','fjnm',NULL),('3600001','贺洋','23','男',NULL,NULL,'47244217','xavc',NULL),('3600002','段军','20','男',NULL,NULL,'84157868','gaue',NULL),('3700001','姜洋','22','女',NULL,NULL,'00307264','trxgg',NULL),('5400001','史娜','22','男',NULL,NULL,'21776475','lydfa',NULL),('6200001','蔡勇','22','男',NULL,NULL,'67409467','zdkur',NULL),('6500002','锺明','23','女',NULL,NULL,'83641003','bwojzq',NULL),('9900001','韩军','22','女',NULL,NULL,'80441299','sxmou',NULL),('9900002','丁磊','21','男',NULL,NULL,'36768113','jquu',NULL);
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teacher`
--

DROP TABLE IF EXISTS `teacher`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teacher` (
  `t_id` varchar(15) NOT NULL,
  `t_name` varchar(20) DEFAULT NULL,
  `t_age` varchar(5) DEFAULT NULL,
  `t_sex` varchar(1) DEFAULT NULL,
  `t_tel` varchar(11) DEFAULT NULL,
  `t_password` varchar(20) DEFAULT NULL,
  `t_img` varchar(45) DEFAULT NULL,
  `t_introduction` text,
  `t_achievement` text,
  PRIMARY KEY (`t_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teacher`
--

LOCK TABLES `teacher` WRITE;
/*!40000 ALTER TABLE `teacher` DISABLE KEYS */;
INSERT INTO `teacher` VALUES ('0','王语文','30','女','13000000000','123456','','毕业于xx大学，获得xx专业学士学位；曾在xx公司工作2年；之后担任xx大学xx专业教师。','在大学期间获得了xx奖、xx、xxxx奖；在xx大学任教期间获得了xx奖、xxx奖。'),('1','王数学','35','男','13111111111','123456',NULL,NULL,NULL),('2','王英语','29','女','13222222222','123456',NULL,NULL,NULL),('3','王政治','50','男','13333333333','123456',NULL,NULL,NULL),('4','王历史','43','女','13444444444','123456',NULL,NULL,NULL),('5','王地理','34','男','13555555555','123456',NULL,NULL,NULL),('6','王物理','42','女','13666666666','123456',NULL,NULL,NULL),('7','王化学','38','男','13777777777','123456',NULL,NULL,NULL),('8','王生物','46','女','13888888888','123456',NULL,NULL,NULL),('9','李语文','45','男','13999999999','123456',NULL,NULL,NULL);
/*!40000 ALTER TABLE `teacher` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-08-30 10:44:55
