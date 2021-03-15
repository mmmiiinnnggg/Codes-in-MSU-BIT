-- MySQL dump 10.16  Distrib 10.1.26-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: db
-- ------------------------------------------------------
-- Server version	10.1.26-MariaDB-0+deb9u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `electronic magazine`
--

DROP TABLE IF EXISTS `electronic magazine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `electronic magazine` (
  `Code` tinyint(4) DEFAULT NULL,
  `Date` varchar(19) DEFAULT NULL,
  `student` varchar(5) DEFAULT NULL,
  `subject` tinyint(4) DEFAULT NULL,
  `type of class` varchar(9) DEFAULT NULL,
  `points` varchar(0) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `electronic magazine`
--

LOCK TABLES `electronic magazine` WRITE;
/*!40000 ALTER TABLE `electronic magazine` DISABLE KEYS */;
INSERT INTO `electronic magazine` VALUES (1,'2019-11-21 00:00:00','1',1,'Lection',''),(2,'2019-11-21 00:00:00','2;3',2,'Lab',''),(3,'2019-11-21 00:00:00','4;5;6',3,'seminar',''),(4,'2019-11-21 00:00:00','7',4,'practical',''),(5,'2019-11-21 00:00:00','8',5,'practical',''),(6,'2019-11-21 00:00:00','9;10',6,'Lection',''),(7,'2019-12-19 00:00:00','11',8,'practical',''),(8,'2019-12-19 00:00:00','12',9,'Lection',''),(9,'2019-12-19 00:00:00','13',10,'seminar',''),(10,'2019-12-19 00:00:00','2;14',11,'Lection',''),(11,'2019-12-19 00:00:00','15',12,'practical',''),(12,'2019-12-19 00:00:00','5;16',13,'seminar',''),(13,'2019-12-19 00:00:00','17',14,'Lection',''),(14,'2019-12-19 00:00:00','7;18',15,'practical',''),(15,'2019-12-19 00:00:00','19',16,'Lab',''),(16,'2019-12-19 00:00:00','20',17,'Lection',''),(17,'2019-12-19 00:00:00','21',18,'seminar',''),(18,'2019-12-19 00:00:00','17;22',22,'Lab',''),(19,'2019-12-19 00:00:00','23',23,'Lab',''),(20,'2019-12-19 00:00:00','24',24,'Lection',''),(21,'2019-12-19 00:00:00','25',7,'seminar',''),(22,'2019-12-19 00:00:00','10;11',20,'seminar',''),(23,'2019-12-19 00:00:00','16;19',25,'Lection',''),(24,'2019-12-19 00:00:00','12;21',11,'practical',''),(25,'2019-12-19 00:00:00','11;19',9,'Lab','');
/*!40000 ALTER TABLE `electronic magazine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kadla`
--

DROP TABLE IF EXISTS `kadla`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `kadla` (
  `codestudent` tinyint(4) DEFAULT NULL,
  `sex` varchar(6) DEFAULT NULL,
  `first name` varchar(3) DEFAULT NULL,
  `name` varchar(3) DEFAULT NULL,
  `father name` varchar(3) DEFAULT NULL,
  `birthday` varchar(19) DEFAULT NULL,
  `number of group` tinyint(4) DEFAULT NULL,
  `nation` varchar(7) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kadla`
--

LOCK TABLES `kadla` WRITE;
/*!40000 ALTER TABLE `kadla` DISABLE KEYS */;
INSERT INTO `kadla` VALUES (11,'female','a11','b11','c11','1999-02-01 00:00:00',2,'China'),(12,'male','a12','b12','c12','1999-02-02 00:00:00',2,'China'),(13,'male','a13','b13','c13','1999-02-03 00:00:00',2,'China'),(14,'female','a14','b14','c14','1999-02-04 00:00:00',2,'Russian'),(15,'male','a15','b15','c15','1999-02-05 00:00:00',2,'China'),(16,'male','a16','b16','c16','1999-02-06 00:00:00',1,'China'),(17,'female','a17','b17','c17','1999-02-07 00:00:00',1,'Russian'),(18,'male','a18','b18','c18','1999-02-08 00:00:00',1,'China'),(19,'female','a19','b19','c19','1999-02-09 00:00:00',1,'USA'),(20,'male','a20','b20','c20','1999-02-10 00:00:00',1,'China'),(21,'female','a21','b21','c21','1999-02-11 00:00:00',2,'Russian'),(22,'male','a22','b22','c22','1999-02-12 00:00:00',2,'China'),(23,'male','a23','b23','c23','1999-02-13 00:00:00',2,'China'),(24,'female','a24','b24','c24','1999-02-14 00:00:00',1,'Russian'),(25,'male','a25','b25','c25','1999-02-15 00:00:00',1,'China'),(1,'male','a1','b1','c1','1999-01-01 00:00:00',1,'Russian'),(2,'male','a2','b2','c2','1999-01-01 00:00:00',1,'China'),(3,'female','a3','b3','c3','1999-01-03 00:00:00',1,'Russian'),(4,'male','a4','b4','c5','1999-01-04 00:00:00',1,'USA'),(5,'female','a5','b5','c5','1999-02-01 00:00:00',1,'Russian'),(6,'female','a6','b6','c6','1999-03-01 00:00:00',2,'China'),(7,'male','a7','b7','c7','1999-04-01 00:00:00',2,'China'),(8,'male','a8','b8','c8','1999-05-01 00:00:00',2,'Russian'),(9,'male','a9','b9','c9','1999-06-01 00:00:00',2,'Russian'),(10,'female','a10','b10','c10','1999-07-04 00:00:00',2,'USA');
/*!40000 ALTER TABLE `kadla` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teaching plan`
--

DROP TABLE IF EXISTS `teaching plan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `teaching plan` (
  `Codesubject` tinyint(4) DEFAULT NULL,
  `rename` varchar(11) DEFAULT NULL,
  `teacher` varchar(8) DEFAULT NULL,
  `hours` tinyint(4) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teaching plan`
--

LOCK TABLES `teaching plan` WRITE;
/*!40000 ALTER TABLE `teaching plan` DISABLE KEYS */;
INSERT INTO `teaching plan` VALUES (1,'math','bolic',50),(2,'physics','alexs',30),(3,'english','daming',20),(4,'russian','elena',40),(5,'computer','jenny',40),(6,'history','profess',15),(7,'math','polosin',50),(8,'english','xiaoming',20),(9,'physics','yiwan',30),(10,'computer','bormel',30),(11,'algebra','tochili',30),(12,'programming','jenny',20),(13,'russian','olega',30),(14,'gernman','olega',20),(15,'gym','chenli',30),(16,'dismath','zalahof',25),(17,'numerical','vlagimil',35),(18,'diffequa','sheglof',45),(19,'math','nikitin',50),(20,'english','dada',15),(21,'gym','baobao',35),(22,'supercomp','bormel',30),(23,'stats','laode',50),(24,'funcala','boris',40),(25,'comptuer','vylitok',30);
/*!40000 ALTER TABLE `teaching plan` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-08-22 15:20:24
