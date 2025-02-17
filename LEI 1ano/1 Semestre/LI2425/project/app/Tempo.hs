module Tempo where

import ImmutableTowers
import LI12425
import Tarefa2 ( terminouJogo )
import Tarefa3 ( atualizaJogo )

reageTempo :: Float -> ImmutableTowers -> ImmutableTowers
reageTempo t it
    | terminouJogo (jogo it) && gameState it == MapScreen && totalTime it > 11 = it {gameState = GameOverScreen}
    | gameState it == MapScreen =
        it { jogo = atualizaJogo t (jogo it)
           , frameState = updateframeState (frameState it)
           , totalTime = totalTime it + t
--           , projeteisAtivos = atualizaProjeteis t (projeteisAtivos it)
           }
    | otherwise = it

updateframeState :: (Int, Int) -> (Int, Int)
updateframeState (x, y)
    | y >= 10 = ((x + 1) `mod` 2, 0)
    | otherwise = (x, y + 1)



-- atualizaProjeteis :: Tempo -> [ProjetilEmVoo] -> [ProjetilEmVoo]
-- atualizaProjeteis dt = map atualizaProjetil
--   where
--     atualizaProjetil p
--       | tempoRestante p <= 0 = p { posicaoAtual = posicaoFinal p }
--       | otherwise = p { posicaoAtual = lerp (posicaoInicial p) (posicaoFinal p) (1 - tempoRestante p / tempoTotal p)
--                       , tempoRestante = tempoRestante p - dt
--                       }

-- -- | Function to update the projectiles Effects
-- atualizaProjetilEffect :: [Inimigos] -> Float -> [Inimigos]
-- atualizaProjetilEffect [] _ = []
-- atualizaProjetilEffect (x:xs) t = aux t (projeteisInimigo x) : atualizaProjetilEffect xs t
--   where
--     aux :: Float -> [Projetil] -> Inimigo
--     aux _ [] = x
--     aux t (y:ys) 
--       | case tipoProjetil y of

-- | Function to interpolate the position of the projectile
lerp :: Posicao -> Posicao -> Float -> Posicao
lerp (x1, y1) (x2, y2) t = (x1 + t * (x2 - x1), y1 + t * (y2 - y1))


-- Primeiro check se o jogo ainda n acabou (terminajogo)
-- Preciso mover os inimigos aqui (atualiza jogo)
-- Adicionar mousetracking quando maybe torre = true
-- ATENÇÂO NA COMPRA DAS TORRES, NÃO PODEM SER COLOCADAS EM CIMA DE OUTRAS, usar o validatorres tarefa 1