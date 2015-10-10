-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Sam 10 Octobre 2015 à 16:08
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
-- Structure de la table `totenun_OF`
--

CREATE TABLE IF NOT EXISTS `totenun_OF` (
`id` int(11) NOT NULL,
  `letter` varchar(1) NOT NULL DEFAULT '',
  `term` varchar(128) DEFAULT NULL,
  `catgram` varchar(128) DEFAULT NULL,
  `definition` varchar(2000) DEFAULT NULL,
  `letter_index` varchar(7) NOT NULL
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=33151 ;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `totenun_OF`
--
ALTER TABLE `totenun_OF`
 ADD PRIMARY KEY (`id`), ADD KEY `letter` (`letter`,`letter_index`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `totenun_OF`
--
ALTER TABLE `totenun_OF`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=33151;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
