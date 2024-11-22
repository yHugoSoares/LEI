{-|
Module:         Ficha 4
Description:    Ficha 4 de LI1
Copyright:      (C) Hugo Soares <hugoferreirasoares@gmail.com>, 2024
Stability:      In development
Portability:    POSIX

Este módulo contém definições Haskell para o cálculo de funções recursivas simples.
-}
module Ficha4 where

import Test.HUnit


{-| Funcao que recebe dois numeros "Float" e devolve a sua divisao.

== __Exemplos de utilização:__
>>> mydiv 4 2
2.0
>>> mydiv 6 2
3.0
>>> mydiv 3 2
1.5
-}
mydiv :: Float -> Float -> Float
mydiv x y = x/y

{-| Funcao que recebe dois numeros "Int" e devolve a sua divisao.

== __Exemplos de utilização:__
>>> mydiv1 4 2
2
>>> mydiv1 6 2
3
>>> mydiv1 3 2
1
-}
mydiv1 :: Int -> Int -> Int
mydiv1 x y = div x y


type Matriz a = [[a]] -- ^Definicao de um tipo Matriz

{-|Uma matriz exemplo [[1, 2, 3], [4, 5, 6], [7, 8, 9]]-}
matrizExemplo1 :: Matriz Int
matrizExemplo1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]] 

{-|Uma matriz exemplo [[1, 2], [3, 4]]-}
matrizExemplo2 :: Matriz Int
matrizExemplo2 = [[1, 2], [3, 4]]

{-| Funcao que recebe uma matriz e troca a primeira linha com a ultima.

== __Exemplos de utilização:__
>>> [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
[[7,8,9],[4,5,6],[1,2,3]]

>>> [[1, 2], [3, 4]]
[3, 4], [1, 2]] 
-}
trocaPrimLinhaUlt :: Matriz a -> Matriz a
trocaPrimLinhaUlt [[]] = []
trocaPrimLinhaUlt [[x]] = [[x]]
trocaPrimLinhaUlt [m] = [m]
trocaPrimLinhaUlt (m:ms) = [last ms] ++ init ms ++ [m]


trocaPrimColunaUlt :: Matriz a -> Matriz a
trocaPrimColunaUlt [[]] = [[]]
trocaPrimColunaUlt [(m:ms)] = [[last ms] ++ (init ms) ++ [m]]
trocaPrimColunaUlt ((m:ms):t) = last ms ++ (init ms) ++ [m] ++ (trocaPrimColunaUlt t)