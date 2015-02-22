<?php

interface IConverter{
  public function convertConjugation(array $conjugation);
  public function convertArray(array $ary);
  public function convertSelect(array $ary);
} // interface IConverter

?>