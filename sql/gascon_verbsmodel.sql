-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Dim 22 Février 2015 à 10:02
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
-- Structure de la table `gascon_verbsmodel`
--

CREATE TABLE IF NOT EXISTS `gascon_verbsmodel` (
`id` int(11) NOT NULL,
  `verb` varchar(25) CHARACTER SET utf8 NOT NULL,
  `nummodel` varchar(5) CHARACTER SET utf8 NOT NULL,
  `see` varchar(16) CHARACTER SET utf8 NOT NULL,
  `alias` int(11) DEFAULT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=35 ;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `gascon_verbsmodel`
--
ALTER TABLE `gascon_verbsmodel`
 ADD PRIMARY KEY (`id`), ADD KEY `verb` (`verb`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `gascon_verbsmodel`
--
ALTER TABLE `gascon_verbsmodel`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=35;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
