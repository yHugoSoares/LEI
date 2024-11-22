module Main where

import Graphics.Gloss

import Desenhar
import Eventos
import ImmutableTowers
import Tempo

janela :: Display
janela = InWindow "Immutable Towers" (1600, 900) (0, 0)

fundo :: Color
fundo = white

fr :: Int
fr = 60

main :: IO ()
main = do
    putStrLn "Hello from Immutable Towers!"

    play janela fundo fr it desenha reageEventos reageTempo
    where
        it = ImmutableTowers {}
