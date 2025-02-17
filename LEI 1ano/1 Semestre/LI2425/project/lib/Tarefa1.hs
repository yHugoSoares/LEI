{-|
Module      : Tarefa1
Description : Invariantes do Jogo
Copyright   : Sívio João Freitas Pontes <a100762@alunos.uminho.pt>
              Hugo Ferreira Soares <a107293@alunos.uminho.pt>


Módulo para a realização da Tarefa 1 de LI1 em 2024/25.
-}
module Tarefa1 where

import LI12425

{-| Esta função verifica se um jogo é válido com os restantes validators.
-}
validaJogo :: Jogo -> Bool
validaJogo jogo =   validaPortais (portaisJogo jogo) (baseJogo jogo) (mapaJogo jogo)
                &&  validaTorres (torresJogo jogo) (mapaJogo jogo)
                &&  validaInimigos (inimigosJogo jogo) (portaisJogo jogo) (mapaJogo jogo)
                &&  validaBase (baseJogo jogo) (mapaJogo jogo)
                &&  existeCaminho (mapaJogo jogo) (baseJogo jogo) (head (portaisJogo jogo))

{-| Esta função verifica se os portais são válidos.

Critérios:

    * A posição do portal não pode ser a mesma que a da base.
    * A posição do portal tem de ser Terra.
-}
validaPortais :: [Portal] -> Base -> Mapa -> Bool
validaPortais [] _ _ = False
validaPortais portais base mapa = all (\p -> terrenoEm (posicaoPortal p) mapa == Terra
    && (posicaoPortal p /= posicaoBase base)) portais

{-| Esta função verifica se os inimigos são válidos.

Critérios:

    * A posição do inimigo tem de ser Terra.
    * A velocidade do inimigo tem de ser positiva.
    * A vida do inimigo tem de ser positiva.
    * Não pode haver projéteis de fogo e gelo ao mesmo tempo.
    * A posição do inimigo tem de ser a mesma que a de um portal.
-}
validaInimigos :: [Inimigo] -> [Portal] -> Mapa -> Bool
validaInimigos inimigos portais mapa = all (\i -> terrenoEm (posicaoInimigo i) mapa == Terra
    && velocidadeInimigo i > 0 && vidaInimigo i > 0
    && not (hasOpposingProjectiles (projeteisInimigo i))) inimigos
    && all (\posInimigo -> any (\posPortal -> posicaoInimigo posInimigo == posicaoPortal posPortal) portais) inimigos

{-| Função de suporte para verificar se têm projéteis de fogo e gelo ao mesmo tempo.
-}
hasOpposingProjectiles :: [Projetil] -> Bool
hasOpposingProjectiles projeteis = any (\p -> tipoProjetil p == Fogo) projeteis && any (\p -> tipoProjetil p == Gelo) projeteis

{-| Esta função verifica se as torres são válidas.

Critérios:

    * A posição da torre tem de ser Relva.
    * O alcance da torre tem de ser positivo.
    * A rajada da torre tem de ser positiva.
    * O ciclo da torre tem de ser positivo.
    * Não pode haver torres sobrepostas.
-}
validaTorres :: [Torre] -> Mapa -> Bool
validaTorres torres mapa = all (\t -> terrenoEm (posicaoTorre t) mapa == Relva
    && alcanceTorre t > 0 && rajadaTorre t > 0 && cicloTorre t > 0) torres && sobrepostoTorres torres

{-| Função de suporte para verificar se há torres sobrepostas.

Critérios:

    * A posição da torre não pode ser a mesma que a de outra torre.
-}
sobrepostoTorres :: [Torre] -> Bool
sobrepostoTorres [] = True -- Nenhuma torre, nenhuma sobreposição
sobrepostoTorres (t:ts) = all (\t' -> posicaoTorre t /= posicaoTorre t') ts && sobrepostoTorres ts

{-| Esta função verifica se a base é válida.

Critérios:

    * A posição da base tem de ser Terra.
    * A vida da base tem de ser positiva.
    * Os créditos da base têm de ser positivos.
-}
validaBase :: Base -> Mapa -> Bool
validaBase base mapa = terrenoEm (posicaoBase base) mapa == Terra && vidaBase base >= 0 && creditosBase base > 0

{-| Esta função verifica se existe um caminho entre a base e o portal.

Critérios:

    * A posição do portal tem de ser alcançável a partir da base.
-}
existeCaminho :: Mapa -> Base -> Portal -> Bool
existeCaminho mapa base portal = existeCaminhoAux mapa (posicaoBase base) (posicaoPortal portal) []
    where
        existeCaminhoAux :: Mapa -> Posicao -> Posicao -> [Posicao] -> Bool
        existeCaminhoAux m (x, y) (x', y') visitados
            | (x, y) == (x', y') = True  -- Base case: reached the portal
            | (x, y) `elem` visitados = False  -- If the position is already visited, no path
            | terrenoEm (x, y) m /= Terra = False  -- If the current position is not Terra, no path
            | otherwise = any (\(nx, ny) -> existeCaminhoAux m (nx, ny) (x', y') ((x, y) : visitados))
                            (adjacentes (x, y) m)

{-| Função de suporte para obter as posições adjacentes a uma dada posição.
-}
adjacentes :: Posicao -> Mapa -> [Posicao]
adjacentes (x, y) mapa = filter (dentroMapa mapa) [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]

{-| Função de suporte para verificar se uma posição está dentro do mapa.
-}
dentroMapa :: Mapa -> Posicao -> Bool
dentroMapa mapa (x, y) = x >= 0 && y >= 0 && y < fromIntegral (length mapa) && x < fromIntegral (length (head mapa))

{-| Função de suporte para obter o terreno numa dada posição.
-}
terrenoEm :: Posicao -> Mapa -> Terreno
terrenoEm (x, y) mapa = mapa !! floor y !! floor x
