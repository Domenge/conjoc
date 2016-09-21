<?php
/**
 * \file      IConverter.inc
 * \author    Domenge Château-Annaud
 * \version   1.0
 * \date      May 2016
 * \brief     interface
 *
 * \details   declares a contract that every Converter must implements.
 */
interface IConverter{
  public function convertConjugation(array $conjugation); /**< */
  public function convertArray(array $ary);
  public function convertSelect(array $ary);
} // interface IConverter

?>