--
-- Base de données: `Chrono-Cross`
--

DROP DATABASE `Chrono-Cross`;

CREATE DATABASE IF NOT EXISTS `Chrono-Cross`;

USE `Chrono-Cross`;

-- --------------------------------------------------------

--
-- Structure de la table `Categorie`
--

CREATE TABLE IF NOT EXISTS `Categorie` (
  `idCategorie` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  `Sexe` enum('M','F') NOT NULL,
  PRIMARY KEY (`idCategorie`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Categorie` (`Nom`, `Sexe`) VALUES
('M13', 'M'),
('M13', 'F'),
('M15', 'M'),
('M15', 'F'),
('M17', 'M'),
('M17', 'F');

-- --------------------------------------------------------

--
-- Structure de la table `Classe`
--

CREATE TABLE IF NOT EXISTS `Classe` (
  `idClasse` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(64) NOT NULL,
  `Numero` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`idClasse`),
  CONSTRAINT Unique_Classe UNIQUE (`Nom`,`Numero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Classe` (`Nom`,`Numero`) VALUES
('6E', '1'),
('6E', '2'),
('6E', '3'),
('5E', '1'),
('5E', '2'),
('5E', '3'),
('4E', '1'),
('4E', '2'),
('4E', '3'),
('3E', '1'),
('3E', '2'),
('3E', '3'),
('2E', '1');

-- --------------------------------------------------------

--
-- Structure de la table `Coureur`
--

CREATE TABLE IF NOT EXISTS `Coureur` (
  `idCoureur` int(11) NOT NULL AUTO_INCREMENT,
  `idCategorie` int(11) NOT NULL,
  `idClasse` int(11) NOT NULL,
  `INE` varchar(11) NOT NULL,
  `Nom` varchar(64) NOT NULL,
  `Prenom` varchar(64) NOT NULL,
  `DateNaissance` date NOT NULL,
  `Sexe` enum('M','F') NOT NULL,
  PRIMARY KEY (`idCoureur`),
  CONSTRAINT Unique_Coureur UNIQUE (`INE`),
  CONSTRAINT Coureur_fk_1 FOREIGN KEY (`idCategorie`) REFERENCES Categorie(`idCategorie`) ON DELETE CASCADE,
  CONSTRAINT Coureur_fk_2 FOREIGN KEY (`idClasse`) REFERENCES Classe(`idClasse`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789AA','PERRICHON','Julia','2004-04-16','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789BB','MOUTARD','Camille','2004-01-08','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789CC','MOLIST','Lucille','2004-09-26','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789DD','RIES','Clementine','2004-06-16','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789EE','LAMOUREUX','Felicia','2004-01-15','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789FF','STEY','Pauline','2004-05-01','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789GG','BIRE-HESLOUIS','Maele','2004-02-27','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789HH','BODIN','Alexia','2004-10-29','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789II','TERREC','Maelle','2004-11-05','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789JJ','FORNES','Marie','2004-02-01','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789KK','WINTREBERT','Pauline','2004-12-04','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789LL','GOURLET','Romane','2004-03-10','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789MM','VINCENT','Ines','2004-04-01','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789NN','DUTOT','Camille','2004-09-13','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('4','7','123456789OO','PREVOST','Emmie','2004-01-02','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891AA','PELIOT','Julien','2004-02-16','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891BB','MOULARD','Charles','2004-03-08','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891CC','DURAND','Lucien','2004-10-26','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891DD','RIOUX','Clement','2004-07-07','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891EE','LAMOUR','Felicien','2004-08-24','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891FF','STEY','Paul','2004-06-25','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891GG','HERROUIS','Maurice','2004-03-09','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891HH','BOTIN','Alexis','2004-11-28','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891II','TORRES','Marcel','2004-12-07','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891JJ','FURLES','Mario','2004-08-01','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891KK','INTERBERT','Alexandre','2004-07-01','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891LL','GOUSSET','Romain','2004-04-17','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891MM','VINEAU','Thomas','2004-05-18','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891NN','PIGNON','Jean','2004-10-20','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('3','7','234567891OO','CLEVOST','Emile','2004-02-21','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910AA','MARTIN','Emma','2002-04-12','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910BB','BERNARD','Louise','2002-06-01','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910CC','PETIT','Jade','2002-02-25','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910DD','BOYER','Alice','2002-01-31','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910EE','DUBOIS','Chloé','2002-03-01','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910FF','MOREAU','Lina','2002-07-14','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910GG','LAURANT','Léa','2002-08-24','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910HH','LEFEVE','Manon','2002-11-10','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910II','LEROY','Rose','2002-10-11','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('6','13','345678910JJ','ROUX','Anna','2002-12-05','F');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101AA','FOURNIER','Gabriel','2002-05-03','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101BB','GIRARD','Louis','2002-06-20','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101CC','BONNET','Raphaël','2002-04-25','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101DD','DUPONT','Jules','2002-09-30','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101EE','LAMBERT','Adam','2002-07-10','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101FF','FONTAINE','Lucas','2002-03-15','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101GG','ROUSESEAU','Léo','2002-05-10','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101HH','LEGRAND','Hugo','2002-01-02','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101II','MULLER','Paul','2002-10-04','M');
INSERT INTO `Coureur` (`idCategorie`,`idClasse`,`INE`,`Nom`,`Prenom`,`DateNaissance`,`Sexe`) VALUES('5','13','456789101JJ','GUERIN','Gabin','2002-12-05','M');
-- --------------------------------------------------------

--
-- Structure de la table `Manifestation`
--

CREATE TABLE IF NOT EXISTS `Manifestation` (
  `idManifestation` int(11) NOT NULL AUTO_INCREMENT,
  `Nom` varchar(255) NOT NULL,
  `Date` date NOT NULL,
  PRIMARY KEY (`idManifestation`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Manifestation` (`Nom`,`Date`) VALUES('Cross College 2019','2019:04:30');
INSERT INTO `Manifestation` (`Nom`,`Date`) VALUES('Cross Lycee 2019','2019:04:30');

--
-- Structure de la table `Course`
--

CREATE TABLE IF NOT EXISTS `Course` (
  `idCourse` int(11) NOT NULL AUTO_INCREMENT,
  `idManifestation` int(11) NOT NULL,
  `Nom` varchar(255) NOT NULL,
  `Distance` int(11) NOT NULL,
  `HeureDepart` time NOT NULL,
  `Etat` enum('ACourir','Prete','EnCours','Arretee','Terminee') NOT NULL DEFAULT 'ACourir',
  PRIMARY KEY (`idCourse`),
  CONSTRAINT Course_fk_1 FOREIGN KEY (`idManifestation`) REFERENCES Manifestation(`idManifestation`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Course` (`idManifestation`, `Nom`, `Distance`, `HeureDepart`, `Etat`) VALUES('1','Cross M15 F','3500','13:00:00', 'ACourir');
INSERT INTO `Course` (`idManifestation`, `Nom`, `Distance`, `HeureDepart`, `Etat`) VALUES('1','Cross M15 M','5000','14:00:00', 'ACourir');
INSERT INTO `Course` (`idManifestation`, `Nom`, `Distance`, `HeureDepart`, `Etat`) VALUES('2','Cross M17 F','3500','15:00:00', 'ACourir');
INSERT INTO `Course` (`idManifestation`, `Nom`, `Distance`, `HeureDepart`, `Etat`) VALUES('2','Cross M17 M','5000','16:00:00', 'ACourir');

-- --------------------------------------------------------

--
-- Structure de la table `Inscrit`
--

CREATE TABLE IF NOT EXISTS `Inscrit` (
  `idInscrit` int(11) NOT NULL AUTO_INCREMENT,
  `idCoureur` int(11) NOT NULL,
  `idCourse` int(11) NOT NULL,
  `NumeroDossard` varchar(16) NOT NULL,
  PRIMARY KEY (`idInscrit`),
  CONSTRAINT Unique_CoureurCourse UNIQUE (`idCoureur`,`idCourse`),
  CONSTRAINT Inscrit_fk_1 FOREIGN KEY (`idCoureur`) REFERENCES Coureur(`idCoureur`) ON DELETE CASCADE,
  CONSTRAINT Inscrit_fk_2 FOREIGN KEY (`idCourse`) REFERENCES Course(`idCourse`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('1','1','101');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('2','1','102');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('3','1','103');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('4','1','104');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('5','1','105');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('6','1','106');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('7','1','107');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('8','1','108');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('9','1','109');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('10','1','110');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('11','1','111');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('12','1','112');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('13','1','113');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('14','1','114');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('15','1','115');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('16','2','201');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('17','2','202');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('18','2','203');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('19','2','204');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('20','2','205');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('21','2','206');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('22','2','207');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('23','2','208');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('24','2','209');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('25','2','210');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('26','2','211');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('27','2','212');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('28','2','213');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('29','2','214');
INSERT INTO `Inscrit` (`idCoureur`,`idCourse`,`NumeroDossard`) VALUES('30','2','215');

-- --------------------------------------------------------

--
-- Structure de la table `Arrivee`
--

CREATE TABLE IF NOT EXISTS `Arrivee` (
  `idArrivee` int(11) NOT NULL AUTO_INCREMENT, 
  `idInscrit` int(11) NOT NULL,
  `Temps` time NOT NULL,
  PRIMARY KEY (`idArrivee`),
  CONSTRAINT Arrivee_fk_1 FOREIGN KEY (`idInscrit`) REFERENCES Inscrit(`idInscrit`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('1','00:12:56');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('2','00:13:44');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('3','00:14:11');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('4','00:14:52');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('5','00:15:17');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('6','00:16:30');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('2','00:17:50');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('8','00:18:54');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('9','00:21:06');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('10','00:21:46');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('11','00:22:08');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('12','00:22:25');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('13','00:23:01');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('14','00:25:06');
INSERT INTO `Arrivee` (`idInscrit`,`Temps`) VALUES('15','00:29:12');

