{-|
Module      : Tarefa1
Description : Invariantes do Jogo
Copyright   : Sívio João Freitas Pontes <a100762@alunos.uminho.pt>
              Hugo Ferreira Soares <a107293@alunos.uminho.pt>


Módulo para a realização da Tarefa 1 de LI1 em 2024/25.
-}
module Tarefa1 where

-- import LI12425

-- validaJogo :: Jogo -> Bool
-- validaJogo jogo = validaPortais (portaisJogo jogo) (mapaJogo jogo)
--                   && validaTorres (torresJogo jogo) (mapaJogo jogo)
--                   && validaInimigos (inimigosJogo jogo) (portaisJogo jogo) (mapaJogo jogo)
--                   && validaBase (baseJogo jogo) (mapaJogo jogo)

-- validaPortais :: [Portal] -> Mapa -> Bool
-- validaPortais portais mapa = all (\p -> terrenoEm (posicaoPortal p) mapa == Terra && not (sobreposto p portais torres base)) portais

-- validaTorres :: [Torre] -> Mapa -> Bool
-- validaTorres torres mapa = all (\t -> terrenoEm (posicaoTorre t) mapa == Relva && not (sobreposto t torres portais base)) torres

-- validaInimigos :: [Inimigo] -> [Portal] -> Mapa -> Bool
-- validaInimigos inimigos portais mapa = all (\i -> terrenoEm (posicaoInimigo i) mapa == Terra && posicaoValida i portais && not (sobreposto i torres portais base)) inimigos

-- validaBase :: Base -> Mapa -> Bool
-- validaBase base mapa = terrenoEm (posicaoBase base) mapa == Terra && not (sobreposto base portais torres)

-- terrenoEm :: Posicao -> Mapa -> Terreno
-- terrenoEm (x, y) mapa = mapa !! y !! x

-- sobreposto :: Entidade -> [Entidade] -> Bool
-- sobreposto entidade outras = any (\e -> posicao e == posicao entidade) outras

-- posicaoValida :: Inimigo -> [Portal] -> Bool
-- posicaoValida inimigo portais = any (\p -> posicaoInimigo inimigo == posicaoPortal p) portais