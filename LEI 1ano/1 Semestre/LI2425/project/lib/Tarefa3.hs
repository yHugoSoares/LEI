{-|
Module      : Tarefa3
Description : Mecânica do Jogo
Copyright   : Sívio João Freitas Pontes <a100762@alunos.uminho.pt>
              Hugo Ferreira Soares <a107293@alunos.uminho.pt>


Módulo para a realização da Tarefa 3 de LI1 em 2024/25.
-}
module Tarefa3 where

import LI12425
import Tarefa2

import Data.List ((\\))

{-| Esta função atualiza o estado do jogo separadamente após um intervalo de tempo.
-}
atualizaJogo :: Tempo -> Jogo -> Jogo
atualizaJogo deltaT jogo = jogoAtualizado
  where
    (inimigosAtualizados, creditosGanhos, novaBase) = atualizaInimigos deltaT (mapaJogo jogo) (baseJogo jogo) (inimigosJogo jogo)
    baseAtualizada = atualizaBase novaBase creditosGanhos inimigosAtualizados
    (torresAtualizadas, inimigosFinal) = atualizaTorres deltaT (torresJogo jogo) inimigosAtualizados
    (portaisAtualizados, novosInimigos) = atualizaPortais deltaT (portaisJogo jogo)
    jogoAtualizado = jogo
      { baseJogo = baseAtualizada,
        torresJogo = torresAtualizadas,
        portaisJogo = portaisAtualizados,
        inimigosJogo = inimigosFinal ++ novosInimigos
      }

{-| Atualiza o estado de todas as torres do jogo.
-}
atualizaTorres :: Tempo -> [Torre] -> [Inimigo] -> ([Torre], [Inimigo])
atualizaTorres deltaT torres inimigos = foldl atualizaTorre ([], inimigos) torres
  where
    atualizaTorre (torresAtualizados, inimigosRestantes) torre
      | tempoTorre torre > 0 = (torresAtualizados ++ [torre { tempoTorre = tempoTorre torre - deltaT }], inimigosRestantes)
      | otherwise =
          let inimigosAlcance = inimigosNoAlcance torre inimigosRestantes
              inimigosAtingidos = take (rajadaTorre torre) inimigosAlcance
              inimigosAtualizados = map (atingeInimigo torre) inimigosAtingidos
              inimigosNaoAtingidos = inimigosRestantes \\ inimigosAtingidos
          in (torresAtualizados ++ [torre { tempoTorre = cicloTorre torre }], inimigosNaoAtingidos ++ inimigosAtualizados)

{-| Atualiza o estado de todos os inimigos do jogo, chama a atualizaInimigo para cada um.
-}
atualizaInimigos :: Tempo -> Mapa -> Base -> [Inimigo] -> ([Inimigo], Creditos, Base)
atualizaInimigos dt mapa base inimigos =
    let
        (inimigosAtualizados, novaBase, mortos) = foldl (\(is, b, ms) inimigo ->
            let (novoInimigo, baseAtualizada) = atualizaInimigo dt mapa b inimigo
            in if vidaInimigo novoInimigo > 0
               then (novoInimigo : is, baseAtualizada, ms) -- Adiciona à lista de inimigos vivos
               else (is, baseAtualizada, novoInimigo : ms) -- Adiciona à lista de inimigos mortos
            ) ([], base, []) inimigos
        -- Calcula os créditos ganhos com inimigos mortos
        creditosGanhos = sum (map butimInimigo mortos)
    in (inimigosAtualizados, creditosGanhos, novaBase)

{- | Atualiza o estado de um inimigo específico, considerando o impacto na base.
-}
atualizaInimigo :: Tempo -> Mapa -> Base -> Inimigo -> (Inimigo, Base)
atualizaInimigo dt mapa base inimigo =
    let novaPos = calculaNovaPos dt mapa (posicaoInimigo inimigo) inimigo (velocidadeInimigo inimigo) (direcaoInimigo inimigo)
        novaDirecao = escolheDirecao mapa (posicaoInimigo inimigo) inimigo (direcaoInimigo inimigo)
        novoInimigo = inimigo { posicaoInimigo = novaPos, direcaoInimigo = novaDirecao }
    in if atingiuBase novoInimigo base
       then
           let novaBase = base { vidaBase = vidaBase base - ataqueInimigo inimigo }
               inimigoMorto = novoInimigo { vidaInimigo = 0 }  -- O inimigo morre ao atingir a base
           in (inimigoMorto, novaBase)  -- Retorna o inimigo morto e a base com a vida reduzida
       else
           (aplicaEfeitosProjeteis dt novoInimigo, base)  -- Atualiza o inimigo com efeitos de projéteis se não atingiu a base

{- | Calcula a nova posição de um inimigo, usa o mapa com o verificaTerrenoProximo para decidir a direção. Mexe com a velocidade e o tempo passado.
-}
calculaNovaPos :: Tempo -> Mapa -> Posicao -> Inimigo -> Float -> Direcao -> Posicao
calculaNovaPos t mapa posicaoAtual inimigo velocidade direcaoAtual =
    let -- Chama a função escolheDirecao para decidir qual direção seguir com base no mapa
        direcaoEscolhida = escolheDirecao mapa posicaoAtual inimigo direcaoAtual
        -- Definir a movimentação baseada na direção
        (dx, dy) = case direcaoEscolhida of
                     Norte -> ( 0 ,  -(t * vfix) )
                     Sul -> ( 0 , t * vfix )
                     Este -> ( t * vfix , 0 )
                     Oeste -> ( -(t * vfix) , 0 )
        -- Calcula a nova posição com base no centro do bloco
        novaPos = (fst posicaoAtual + dx, snd posicaoAtual + dy)
    in novaPos
  where
    vfix = if velocidade < 0 then 0 else velocidade

{-| Verifica o terreno próximo ao inimigo e escolhe a melhor direção a seguir.
-}
verificaTerrenoProximo :: Mapa -> Posicao -> Direcao -> [(Direcao, Terreno)]
verificaTerrenoProximo mapa (x, y) direcaoAtual=
  let direcoes = [(Sul,   (xx, yy+1)),   -- Direção Sul
                  (Norte, (xx, yy-1)), -- Direção Norte
                  (Este,  (xx+1, yy)),   -- Direção Este
                  (Oeste, (xx-1, yy))] -- Direção Oeste
      -- Filtra as posições válidas dentro do mapa
      posicoesValidas = filter (\(_, (i, j)) -> i >= 0 && j >= 0 && i <= 7 && j <= 7) direcoes
      -- Mapeia as posições para suas respectivas direções e terrenos
      terrenos = map (\(dir, (i, j)) -> (dir, mapa !! j !! i)) posicoesValidas
  in  terrenos  -- Retorna todas as direções e terrenos válidos
  where
    xx
      | (x - fromIntegral (floor x :: Int)) >= 0.5 && direcaoAtual == Este = floor x
      | (x - fromIntegral (ceiling x :: Int)) < 0 && direcaoAtual == Oeste = ceiling x
      | otherwise = round x
    yy
      | (y - fromIntegral (floor y :: Int)) >= 0.5 && direcaoAtual == Sul = floor y
      | (y - fromIntegral (ceiling y :: Int)) < 0 && direcaoAtual == Norte = ceiling y
      | otherwise = round y

{-| Escolhe a melhor direção para o inimigo seguir, com base no terreno próximo.
-}
escolheDirecao :: Mapa -> Posicao -> Inimigo -> Direcao -> Direcao
escolheDirecao mapa pos inimigo direcaoAtual =
  let direcoesTerreno = verificaTerrenoProximo mapa pos direcaoAtual
  in case lookup direcaoAtual direcoesTerreno of
       -- Caso 1: Direção atual é "Terra", continua na mesma direção
       Just Terra -> direcaoAtual
       -- Caso 2: Direção atual não é "Terra", escolhe alternativas
       _          -> escolheAlternativa direcaoAtual direcoesTerreno
  where
    -- Função auxiliar para escolher entre direções alternativas
    escolheAlternativa :: Direcao -> [(Direcao, Terreno)] -> Direcao
    escolheAlternativa Norte terrenos = escolherMelhor [Este, Oeste] terrenos
    escolheAlternativa Sul   terrenos = escolherMelhor [Este, Oeste] terrenos
    escolheAlternativa Este  terrenos = escolherMelhor [Norte, Sul] terrenos
    escolheAlternativa Oeste terrenos = escolherMelhor [Norte, Sul] terrenos
    -- Função que escolhe a melhor direção entre as alternativas possíveis
    escolherMelhor :: [Direcao] -> [(Direcao, Terreno)] -> Direcao
    escolherMelhor alternativas terrenos =
      case filter (\(dir, terreno) -> dir `elem` alternativas && terreno == Terra) terrenos of
        ((dir, _):_) -> dir  -- Retorna a primeira direção válida encontrada
        []           -> direcaoInimigo inimigo  -- Caso nenhuma alternativa seja válida

{-| Atualiza o estado de um inimigo, aplicando os efeitos dos projéteis(Slow, Freeze, Burn).
-}
aplicaEfeitosProjeteis :: Tempo -> Inimigo -> Inimigo
aplicaEfeitosProjeteis dt inimigo = aux dt (projeteisInimigo inimigo) inimigo{projeteisInimigo = []} 
  where
    aux :: Tempo -> [Projetil] -> Inimigo -> Inimigo
    aux _ [] ini = ini
    aux t (projetil:ps) ini = if duracaonova <= 0
      then case tipoProjetil projetil of
        Resina -> aux t ps inimigoAtualizado {velocidadeInimigo = velocidadeInimigo ini*2}
        Gelo -> aux t ps inimigoAtualizado {velocidadeInimigo = -velocidadeInimigo ini}
        _ -> aux t ps inimigoAtualizado
      else case tipoProjetil projetil of
        Fogo -> aux t ps inimigoAtualizadoFogo
        Gelo -> aux t ps inimigoAtualizadoGelo
        Resina -> aux t ps inimigoAtualizadoResina
      where
        inimigoAtualizadoFogo = ini { vidaInimigo = vidaInimigo ini - (vidaInimigo ini*0.05*dt), projeteisInimigo =  projetilAtualizado: projeteisInimigo ini }
        inimigoAtualizadoGelo = if velocidadeInimigo ini < 0 then ini
                else ini { velocidadeInimigo = -(velocidadeInimigo ini), projeteisInimigo = projetilAtualizado: projeteisInimigo ini }
        inimigoAtualizadoResina = if velocidadeInimigo ini < 1 then ini
                else ini { velocidadeInimigo = velocidadeInimigo ini*0.5, projeteisInimigo = projetilAtualizado: projeteisInimigo ini }
        inimigoAtualizado = ini { projeteisInimigo = if length (projeteisInimigo ini) > 1 then tail (projeteisInimigo ini) else [] }
        projetilAtualizado = projetil { duracaoProjetil = duracaonova }
        duracaonova = duracaoProjetil projetil - Finita t

{-| Atualiza a base do jogo, adicionando os créditos ganhos e atualizando a vida da base.
-}
atualizaBase :: Base -> Creditos -> [Inimigo] -> Base
atualizaBase base creditosGanhos inimigos =
    let baseComCreditos = base { creditosBase = creditosBase base + creditosGanhos }
        baseAtualizada = foldl atualizaVidaBase baseComCreditos inimigos
    in baseAtualizada

{-| Atualiza a vida da base, subtraindo o dano causado por um inimigo.
-}
atualizaVidaBase :: Base -> Inimigo -> Base
atualizaVidaBase base inimigo =
    if atingiuBase inimigo base
    then base { vidaBase = max 0 (vidaBase base - ataqueInimigo inimigo) }
    else base

{-| Verifica se um inimigo atingiu a base.
-}
atingiuBase :: Inimigo -> Base -> Bool
atingiuBase inimigo base =
    let (x1, y1) = posicaoInimigo inimigo
        (x2, y2) = posicaoBase base
        distanceSquared = (x2 - x1)^(2::Int) + (y2 - y1)^(2::Int)
    in distanceSquared < 1  -- Check if the distance squared is less than 1 (i.e., within 1 unit distance)

{-| Atualiza o estado de todos os portais do jogo.
-}
atualizaPortais :: Tempo -> [Portal] -> ([Portal], [Inimigo])
atualizaPortais deltaT = foldl atualizaPortal ([], [])
  where
    atualizaPortal (portaisAtualizados, novosInimigos) portal =
      let ondas = ondasPortal portal
      in if null ondas
         then (portaisAtualizados ++ [portal], novosInimigos)
         else
           let (ondaAtualizada, inimigosDaOnda) = atualizaOnda deltaT (head ondas)
               novasOndas = case ondaAtualizada of
                              Just onda -> onda : tail ondas
                              Nothing -> tail ondas
           in (portaisAtualizados ++ [portal { ondasPortal = novasOndas }], novosInimigos ++ inimigosDaOnda)

{-| Atualiza o estado de uma onda de inimigos, retornando a onda atualizada e os inimigos a serem adicionados ao jogo.
-}
atualizaOnda :: Tempo -> Onda -> (Maybe Onda, [Inimigo])
atualizaOnda deltaT onda
  | entradaOnda onda > 0 = (Just onda { entradaOnda = entradaOnda onda - deltaT }, [])
  | tempoOnda onda > 0 = (Just onda { tempoOnda = tempoOnda onda - deltaT }, [])
  | null (inimigosOnda onda) = (Nothing, [])
  | otherwise =
      case inimigosOnda onda of
        (primeiroInimigo:restoInimigos) ->
          let inimigoAtualizado = if tempoOnda onda <= 1.5
                                  then primeiroInimigo { posicaoInimigo = posicaoPortal (Portal (posicaoInimigo primeiroInimigo) []) }
                                  else primeiroInimigo
          in (Just onda { inimigosOnda = restoInimigos, tempoOnda = cicloOnda onda }, [inimigoAtualizado])
        [] -> (Nothing, [])