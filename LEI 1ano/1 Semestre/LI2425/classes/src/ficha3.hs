{-|
Module:         Ficha 3
Description:    Ficha 3 de LI1
Copyright:      (C) Hugo Soares <hugoferreirasoares@gmail.com>, 2024
Stability:      In development
Portability:    POSIX

Este módulo contém definições Haskell para o cálculo de funções recursivas simples.
-}
module Ficha3 where
{-|Função que recebe uma lista de strings e remove todas as strings iniciadas por um dado caracter.

== __Exemplos de utilização:__

>>> remove ["abc", "def", "ghi", "jkl"] 'a'
["def","ghi","jkl"]
>>> remove ["abc", "def", "ghi", "jkl"] 'd'
["abc","ghi","jkl"]
>>> remove ["abc", "def", "ghi", "jkl"] 'j'
["abc","def","ghi","jkl"] 
-}
remove :: [String] -> Char -> [String]
remove [] _ = []
remove ((x:xs):t) c = if (x == c) then (remove t c) else ((x:xs) : remove t c)


{-|Função recursiva que recebe uma lista de pares de inteiros e adiciona um valor dado à primeira componente de cada par.
== __Exemplos de utilização:__
>>> addFirst [(1,2), (3,4), (5,6)] 2
[(3,2),(5,4),(7,6)]
>>> addFirst [(1,2), (3,4), (5,6)] 3
[(4,2),(6,4),(8,6)]
-}
type Par = (Int, Int)
addFirst :: [Par] -> Int -> [Par]
addFirst [] _ = []
addFirst ((a,b):t) x = ((a+x),b) : addFirst t x

