module Ficha4_Spec where

import Ficha4
import Test.HUnit

testsMyDiv = test [
    "4/2" ~: 2 ~=? mydiv 4 2,
    "6/2" ~: 3 ~=? mydiv 6 2,
    "3/2" ~: 1.5 ~=? mydiv 3 2
    ]
 

testsMyDiv1 = test [
    "4/2" ~: 2 ~=? mydiv1 4 2,
    "6/2" ~: 3 ~=? mydiv1 6 2,
    "3/2" ~: 1 ~=? mydiv1 3 2
    ]

testsTrocaPrimLinhaUlt = test [
    "Teste 1" ~: [[7,8,9],[4,5,6],[1,2,3]] ~=? trocaPrimLinhaUlt matrizExemplo1,
    "Teste 2" ~: [[3, 4], [1, 2]] ~=? trocaPrimLinhaUlt matrizExemplo2 
    ]