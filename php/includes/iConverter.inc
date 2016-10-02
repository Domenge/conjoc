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
  public function convertConjugation(array $conjugation); /**< \param $conjugation an array containing the conjugation to convert  */
  public function convertArray(array $ary); /**< \param $ary the array to convert*/
  public function convertSelect(array $ary);  /**< \param $ary an array containing the listbox options to convert*/
} // interface IConverter

?>