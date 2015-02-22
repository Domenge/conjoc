-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Dim 22 Février 2015 à 09:58
-- Version du serveur :  5.5.36
-- Version de PHP :  5.4.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `labo.macarel.net`
--

-- --------------------------------------------------------

--
-- Structure de la table `sauzet_model`
--

CREATE TABLE IF NOT EXISTS `sauzet_model` (
  `nummodel` varchar(5) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `verb_prime` varchar(16) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `label_conjugation` varchar(64) CHARACTER SET latin1 COLLATE latin1_general_ci NOT NULL,
  `conjugations` varchar(600) CHARACTER SET latin1 COLLATE latin1_general_ci DEFAULT NULL,
  `is_manual` tinyint(1) DEFAULT NULL,
  `extras` varchar(32) DEFAULT NULL,
  `impersonal` tinyint(1) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `sauzet_model`
--
ALTER TABLE `sauzet_model`
 ADD UNIQUE KEY `numodel` (`nummodel`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
