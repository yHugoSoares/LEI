{-|
Module:         Mini Teste 2
Description:    Mini Teste 2 de LI1
Copyright:      (C) Hugo Soares <hugoferreirasoares@gmail.com>, 2024
Stability:      In development
Portability:    POSIX

Este módulo contém definições Haskell para o cálculo de funções recursivas simples.
-}

module Mini_Teste2 where
import Test.HUnit

{-| Funcao que recebe uma lista de inteiros e um inteiro e devolve o indice da primeira ocorrencia do inteiro na lista.

== __Exemplos de utilização:__
>>> f [1,2,3,4,5] 3
2
>>> f [1,2,3,4,5] 5
4
-}
-- f :: [Int] -> Int -> Maybe Int
-- f l x = procura x li
--     where li = zip l [0..]
--         procura x [] = Nothing
--         procura x ((y,n):ys) 
--             | x==y = Just n
--             | otherwise = procura x ys

g :: [[String]] -> [(String, Int)]
g filas = zip pessoas [1..]
    where pessoas = concat filas

