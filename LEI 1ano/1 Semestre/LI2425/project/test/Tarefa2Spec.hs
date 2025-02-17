module Tarefa2Spec (testesTarefa2) where

import Test.HUnit
import LI12425
import Tarefa2

testesTarefa2 :: Test
testesTarefa2 =
  TestLabel "Testes Tarefa 2" $
    test
      [ "inimigosNoAlcance - não deteta inimigos" ~: 1 ~=? length(inimigosNoAlcance (torre1 Fogo) [inimigo1]),
        "atingeInimigo - dano inválido" ~: 5 ~=? vidaInimigo(atingeInimigo (torre1 Fogo) inimigo1),
        "sinergia Fogo/Gelo - não se cancelam" ~: 0 ~=?
        length(projeteisInimigo (atingeInimigo (torre1 Fogo) (atingeInimigo (torre1 Gelo) inimigo1))),
        "sinergia Fogo/Resina - não duplica" ~: Finita 10 ~=?
        duracaoProjetil (head (projeteisInimigo (atingeInimigo (torre1 Resina) (atingeInimigo (torre1 Fogo) inimigo1)))),
        "sinergia Fogo/Fogo - não adiciona" ~: Finita 10 ~=? 
        duracaoProjetil (head (projeteisInimigo (atingeInimigo (torre1 Fogo) (atingeInimigo (torre1 Fogo) inimigo1)))),
        "sinergia Gelo/Gelo - não adiciona" ~: Finita 10 ~=?
        duracaoProjetil (head (projeteisInimigo (atingeInimigo (torre1 Gelo) (atingeInimigo (torre1 Gelo) inimigo1)))),
        "sinergia Resina/Resina - não adiciona" ~: Finita 10 ~=?
        duracaoProjetil (head (projeteisInimigo (atingeInimigo (torre1 Resina) (atingeInimigo (torre1 Resina) inimigo1)))),
        "ativaInimigo - ativa inimigo incorretamente" ~: 1 ~=? length(snd(ativaInimigo portal1 [])),
        "ganhouJogo - não ganhou" ~: True ~=? ganhouJogo jogoGanho,
        "perdeuJogo - ganhou" ~: True ~=? perdeuJogo jogoPerdido
      ]

jogoGanho :: Jogo
jogoGanho = Jogo
        { baseJogo = Base
            { vidaBase = 100
            , posicaoBase = (0, 1)
            , creditosBase = 1000
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 2)
            , ondasPortal = []
            }]
        , torresJogo = []
        , mapaJogo = mapa01
        , inimigosJogo = []
        , lojaJogo = []
        }

jogoPerdido :: Jogo
jogoPerdido = Jogo
        { baseJogo = Base
            { vidaBase = 0
            , posicaoBase = (0, 1)
            , creditosBase = 1000
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 2)
            , ondasPortal = [Onda
                { inimigosOnda = [inimigo1, inimigo1]
                , cicloOnda = 5
                , tempoOnda = 5
                , entradaOnda = 5
                }]
            }]
        , torresJogo = []
        , mapaJogo = mapa01
        , inimigosJogo = []
        , lojaJogo = []
        }

portal1 :: Portal
portal1 = Portal
          { posicaoPortal = (7, 2)
          , ondasPortal = [Onda
              { inimigosOnda = [inimigo1]
              , cicloOnda = 1
              , tempoOnda = 5
              , entradaOnda = 5
              }]
            }

torre1 :: TipoProjetil -> Torre
torre1 tp = Torre
          { posicaoTorre = (7, 1)
          , danoTorre = 5
          , alcanceTorre = 3
          , rajadaTorre = 1
          , cicloTorre = 1
          , tempoTorre = 1
          , projetilTorre = Projetil tp (Finita 5)
          }

inimigo1 :: Inimigo
inimigo1 = Inimigo
    { posicaoInimigo = (7,2)
    , direcaoInimigo = Oeste
    , vidaInimigo = 10
    , velocidadeInimigo = 1
    , ataqueInimigo = 15
    , butimInimigo = 50
    , projeteisInimigo = []
    }

mapa01 :: Mapa
mapa01=[[t, t, r, r, a, a, a, r],
        [r, t, r, r, a, r, r, r],
        [r, t, r, r, a, r, t, t],
        [r, t, r, r, a, r, t, r],
        [r, t, r, r, a, r, t, r],
        [r, t, t, t, t, t, t, r],
        [r, r, r, r, a, r, r, r],
        [r, r, r, a, a, r, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua