{-# OPTIONS_GHC -Wno-orphans #-}
{-|
Module      : Tarefa2
Description : Auxiliares do Jogo
Copyright   : Sívio João Freitas Pontes <a100762@alunos.uminho.pt>
              Hugo Ferreira Soares <a107293@alunos.uminho.pt>


Módulo para a realização da Tarefa 2 de LI1 em 2024/25.
-}
module Tarefa2 where

import LI12425

{-|
Instância da classe 'Num' para o tipo 'Duracao'.

Esta instância define como as durações infinitas e finitas se comportam
quando somadas, multiplicadas, ou quando são aplicadas as funções 'abs',
'signum' e 'fromInteger'.
-}
instance Num Duracao where
    Infinita + _ = Infinita
    _ + Infinita = Infinita
    Finita d + Finita d' = Finita (d + d')

    Infinita * _ = Infinita
    _ * Infinita = Infinita
    Finita d * Finita d' = Finita (d * d')

    abs Infinita = Infinita
    abs (Finita d) = Finita (abs d)

    signum Infinita = Finita 1
    signum (Finita d) = Finita (signum d)

    fromInteger n = Finita (fromInteger n)

    negate Infinita = Infinita
    negate (Finita d) = Finita (negate d)

{-| Esta função calcula a distância entre duas posições.
-}
distancia :: Posicao -> Posicao -> Float
distancia (x, y) (x', y') = sqrt ((x - x')^(2 :: Int) + (y - y')^(2 :: Int))

{-| Utilizando a função 'distancia', esta função calcula a distância entre a posição da torre e a posição do inimigo.
-}
inimigosNoAlcance :: Torre -> [Inimigo] -> [Inimigo]
inimigosNoAlcance torre = filter (\i -> distancia (posicaoTorre torre) (posicaoInimigo i) <= alcanceTorre torre)

{-| Esta função calcula o dano que a torre causa ao inimigo e autualiza a sua lista de projéteis.
-}
atingeInimigo :: Torre -> Inimigo -> Inimigo
atingeInimigo torre inimigo = inimigo {vidaInimigo = vidaInimigo inimigo - danoTorre torre, projeteisInimigo = lidaProjetil (projeteisInimigo inimigo) (projetilTorre torre)}
    where
        lidaProjetil :: [Projetil] -> Projetil -> [Projetil]
        lidaProjetil pinimigo ptorre
            | tipoProjetil ptorre == Fogo && any (\p -> tipoProjetil p == Gelo) pinimigo
                = filter (\p -> tipoProjetil p /= Gelo && tipoProjetil p /= Gelo) pinimigo
            | tipoProjetil ptorre == Gelo && any (\p -> tipoProjetil p == Fogo) pinimigo
                = filter (\p -> tipoProjetil p /= Gelo && tipoProjetil p /= Gelo) pinimigo
            | tipoProjetil ptorre == Resina && any (\p -> tipoProjetil p == Fogo) pinimigo
                = map (\p -> if tipoProjetil p == Fogo then p {duracaoProjetil = duplica (duracaoProjetil p)} else p) pinimigo ++ [ptorre]
            | tipoProjetil ptorre == Fogo && any (\p -> tipoProjetil p == Resina) pinimigo
                = pinimigo ++ [ptorre{duracaoProjetil = duplica (duracaoProjetil ptorre)}]
            | otherwise = combinaProjetil pinimigo ptorre
            where
                duplica :: Duracao -> Duracao -- tive que adicionar aos imports na duração o infinito e o finito
                duplica Infinita = Infinita
                duplica (Finita d) = Finita (2 * d)
                combinaProjetil :: [Projetil] -> Projetil -> [Projetil]
                combinaProjetil [] pt = [pt]
                combinaProjetil (x:xs) pt
                    | tipoProjetil x == tipoProjetil pt = (x {duracaoProjetil = duracaoProjetil x + duracaoProjetil pt}) : xs
                    | otherwise = x : combinaProjetil xs pt

{-| Esta função atualiza a lista de inimigos, retirando os que já foram derrotados.
-}
ativaInimigo :: Portal -> [Inimigo] -> (Portal, [Inimigo])
ativaInimigo portal inimigos = (portalAtualizado, inimigosAtualizados)
    where
        -- Pega a primeira onda de inimigos do portal
        primeiraOnda = head (ondasPortal portal)
        -- Separamos o primeiro inimigo da onda e atualizamos sua posição
        primeiroInimigo = (head (inimigosOnda primeiraOnda)) { posicaoInimigo = posicaoPortal portal }
        -- Atualizamos a lista de inimigos ao incluir o primeiro da onda
        inimigosAtualizados = primeiroInimigo : inimigos
        -- Atualizamos a onda removendo o primeiro inimigo
        ondaAtualizada = primeiraOnda { inimigosOnda = tail (inimigosOnda primeiraOnda) }
        -- Atualizamos o portal com a onda modificada
        portalAtualizado
            | null (inimigosOnda ondaAtualizada) = portal { ondasPortal = tail (ondasPortal portal) }
            | otherwise = portal { ondasPortal = ondaAtualizada : tail (ondasPortal portal) }

{-|
Verifica se o jogo terminou.

Um jogo é considerado terminado se o jogador ganhou ou perdeu.
-}
terminouJogo :: Jogo -> Bool
terminouJogo jogo = ganhouJogo jogo || perdeuJogo jogo

{-|
Verifica se o jogador ganhou o jogo.

O jogador ganha o jogo se não houver mais inimigos e não houver mais ondas de inimigos nos portais.
 
return 'True' se o jogador ganhou o jogo, 'False' caso contrário.
-}
ganhouJogo :: Jogo -> Bool
ganhouJogo jogo = null (inimigosJogo jogo) && null (ondasPortal (head (portaisJogo jogo)))

{-|
Verifica se o jogador perdeu o jogo.

O jogador perde o jogo se a vida da base for menor ou igual a zero.

return 'True' se o jogador perdeu o jogo, 'False' caso contrário.
-}
perdeuJogo :: Jogo -> Bool
perdeuJogo jogo = vidaBase (baseJogo jogo) <= 0
