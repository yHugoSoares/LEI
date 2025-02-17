module Tarefa3Spec (testesTarefa3) where

import Test.HUnit
import Tarefa3
import LI12425

testesTarefa3 :: Test
testesTarefa3 =
  TestLabel "Testes Tarefa 3" $
    test
      [ "não move inimigos" ~: (5.5,2.0) ~=?
      posicaoInimigo (head (inimigosJogo (atualizaJogo tempoInicial jogoInicialInim))),
        "não dá spawn de inimigos" ~: 1 ~=?
        length (inimigosJogo (atualizaJogo tempoInicial jogoInicialOnda))
        ]

tempoInicial :: Tempo
tempoInicial = 1.5 -- Defina o tempo inicial

jogoInicialInim :: Jogo
jogoInicialInim = Jogo
        { baseJogo = Base
            { vidaBase = 100
            , posicaoBase = (0, 0)
            , creditosBase = 1000
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 2)
            , ondasPortal = []
            }]
        , torresJogo = []
        , mapaJogo = mapa01
        , inimigosJogo = [inimigo1 (7, 2) Oeste]
        , lojaJogo = listaTorresLoja
        }

jogoInicialOnda :: Jogo
jogoInicialOnda = Jogo
        { baseJogo = Base
            { vidaBase = 100
            , posicaoBase = (0, 0)
            , creditosBase = 1000
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 2)
            , ondasPortal = onda1
            }]
        , torresJogo = []
        , mapaJogo = mapa01
        , inimigosJogo = [inimigo1 (7, 2) Oeste]
        , lojaJogo = listaTorresLoja
        }

onda1 :: [Onda]
onda1 = [Onda
    { inimigosOnda = [inimigo1 (7, 2) Oeste]
    , cicloOnda = 1
    , tempoOnda = 1
    , entradaOnda = 1
    }]

inimigo1 :: Posicao -> Direcao -> Inimigo
inimigo1 posPortal direcao = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = 50
    , velocidadeInimigo = 1
    , ataqueInimigo = 30
    , butimInimigo = 50
    , projeteisInimigo = []
    }

listaTorresLoja :: Loja
listaTorresLoja = [(250, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 10
            , alcanceTorre = 2
            , rajadaTorre = 2
            , cicloTorre = 6
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Fogo
                , duracaoProjetil = Finita 5
                }
            }),
            (150, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 3
            , alcanceTorre = 2
            , rajadaTorre = 2
            , cicloTorre = 6
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Resina
                , duracaoProjetil = Finita 5
                }
            }),
            (200, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 10
            , alcanceTorre = 2
            , rajadaTorre = 2
            , cicloTorre = 6
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Gelo
                , duracaoProjetil = Finita 5
                }
            })]

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