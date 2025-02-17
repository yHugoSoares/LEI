module ImmutableTowers where

import Graphics.Gloss

import LI12425

data GameState = TitleScreen | LevelScreen | MapScreen | BuyScreen | PauseScreen | MapErrorScreen | GameOverScreen
    deriving (Eq, Show)

data ImmutableTowers = ImmutableTowers
    { gameState :: GameState
    , torreComprada :: Maybe Torre
    , jogo :: Jogo
    , imgs :: [Picture]
    , frameState :: (Int,Int)
    , totalTime :: Float
    , selectedSquare :: Maybe Posicao
    , projeteisAtivos :: [ProjetilEmVoo]
    }

data ProjetilEmVoo = ProjetilEmVoo
  { posicaoInicial :: Posicao
  , posicaoFinal :: Posicao
  , posicaoAtual :: Posicao
  , tempoRestante :: Tempo
  , tempoTotal :: Tempo
  , tipoProjetilEmVoo :: TipoProjetil
  }

-- | Vida Base Inicial
vidaBaseInicial :: Float
vidaBaseInicial = 100

initialStateMap1 :: [Picture] -> ImmutableTowers
initialStateMap1 imgs = ImmutableTowers
    { gameState = TitleScreen
    , torreComprada = Nothing
    , jogo = Jogo
        { baseJogo = Base
            { vidaBase = vidaBaseInicial
            , posicaoBase = (0, 1)  -- Ensure this position is on Terra
            , creditosBase = 750
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 2)  -- Ensure this position is on Terra
            , ondasPortal = onda3
            }]
        , torresJogo = []
        , mapaJogo = mapa03
        , inimigosJogo = []
        , lojaJogo = listaTorresLoja
        }
    , imgs = imgs
    , frameState = (0,0)
    , totalTime = 0
    , selectedSquare = Nothing
    , projeteisAtivos = []
    }

initialStateMap2 :: [Picture] -> ImmutableTowers
initialStateMap2 imgs = ImmutableTowers
    { gameState = TitleScreen
    , torreComprada = Nothing
    , jogo = Jogo
        { baseJogo = Base
            { vidaBase = vidaBaseInicial
            , posicaoBase = (0, 0)  -- Ensure this position is on Terra
            , creditosBase = 750
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 2)  -- Ensure this position is on Terra
            , ondasPortal = onda1
            }]
        , torresJogo = []
        , mapaJogo = mapa01
        , inimigosJogo = []
        , lojaJogo = listaTorresLoja
        }
    , imgs = imgs
    , frameState = (0,0)
    , totalTime = 0
    , selectedSquare = Nothing
    , projeteisAtivos = []
    }

initialStateMap3 :: [Picture] -> ImmutableTowers
initialStateMap3 imgs = ImmutableTowers
    { gameState = TitleScreen
    , torreComprada = Nothing
    , jogo = Jogo
        { baseJogo = Base
            { vidaBase = vidaBaseInicial
            , posicaoBase = (3, 0)  -- Ensure this position is on Terra
            , creditosBase = 750
            }
        , portaisJogo = [Portal
            { posicaoPortal = (7, 6)  -- Ensure this position is on Terra
            , ondasPortal = onda2
            }]
        , torresJogo = []
        , mapaJogo = mapa02
        , inimigosJogo = []
        , lojaJogo = listaTorresLoja
        }
    , imgs = imgs
    , frameState = (0,0)
    , totalTime = 0
    , selectedSquare = Nothing
    , projeteisAtivos = []
    }

onda1 :: [Onda]
onda1 = [Onda
    { inimigosOnda = [inimigo1 (7, 2) Oeste, inimigo1 (7, 2) Oeste, inimigo1 (7, 2) Oeste, inimigo1 (7, 2) Oeste]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo2 (7, 2) Oeste, inimigo2 (7, 2) Oeste, inimigo2 (7, 2) Oeste, inimigo2 (7, 2) Oeste]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo3 (7, 2) Oeste, inimigo3 (7, 2) Oeste, inimigo3 (7, 2) Oeste, inimigo3 (7, 2) Oeste]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo4 (7, 2) Oeste, inimigo4 (7, 2) Oeste, inimigo4 (7, 2) Oeste, inimigo4 (7, 2) Oeste]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo5 (7, 2) Oeste, inimigo5 (7, 2) Oeste, inimigo5 (7, 2) Oeste, inimigo5 (7, 2) Oeste]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    }]

onda2 :: [Onda]
onda2 = [Onda
    { inimigosOnda = [inimigo1 (7, 6) Norte, inimigo1 (7, 6) Norte, inimigo1 (7, 6) Norte, inimigo1 (7, 6) Norte]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo2 (7, 6) Norte, inimigo2 (7, 6) Norte, inimigo2 (7, 6) Norte, inimigo2 (7, 6) Norte]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo3 (7, 6) Norte, inimigo3 (7, 6) Norte, inimigo3 (7, 6) Norte, inimigo3 (7, 6) Norte]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo4 (7, 6) Norte, inimigo4 (7, 6) Norte, inimigo4 (7, 6) Norte, inimigo4 (7, 6) Norte]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo5 (7, 6) Norte, inimigo5 (7, 6) Norte, inimigo5 (7, 6) Norte, inimigo5 (7, 6) Norte]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    }]

onda3 :: [Onda]
onda3 = [Onda
    { inimigosOnda = [inimigo1 (7, 2) Sul, inimigo1 (7, 2) Sul, inimigo1 (7, 2) Sul, inimigo1 (7, 2) Sul]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo2 (7, 2) Sul, inimigo2 (7, 2) Sul, inimigo2 (7, 2) Sul, inimigo2 (7, 2) Sul]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo3 (7, 2) Sul, inimigo3 (7, 2) Sul, inimigo3 (7, 2) Sul, inimigo3 (7, 2) Sul]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo4 (7, 2) Sul, inimigo4 (7, 2) Sul, inimigo4 (7, 2) Sul, inimigo4 (7, 2) Sul]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    },
    Onda
    { inimigosOnda = [inimigo5 (7, 2) Sul, inimigo5 (7, 2) Sul, inimigo5 (7, 2) Sul, inimigo5 (7, 2) Sul]
    , cicloOnda = 1
    , tempoOnda = 5
    , entradaOnda = 5
    }]


-- Define example enemies
inimigo1 :: Posicao -> Direcao -> Inimigo
inimigo1 posPortal direcao = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = 50
    , velocidadeInimigo = 1
    , ataqueInimigo = 5
    , butimInimigo = 25
    , projeteisInimigo = []
    }

inimigo2 :: Posicao -> Direcao -> Inimigo
inimigo2 posPortal direcao = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = 60
    , velocidadeInimigo = 1.2
    , ataqueInimigo = 10
    , butimInimigo = 35
    , projeteisInimigo = []
    }

inimigo3 :: Posicao -> Direcao -> Inimigo
inimigo3 posPortal direcao = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = 70
    , velocidadeInimigo = 1.4
    , ataqueInimigo = 12.5
    , butimInimigo = 40
    , projeteisInimigo = []
    }

inimigo4 :: Posicao -> Direcao -> Inimigo
inimigo4 posPortal direcao = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = 80
    , velocidadeInimigo = 1.6
    , ataqueInimigo = 20
    , butimInimigo = 40
    , projeteisInimigo = []
    }

inimigo5 :: Posicao -> Direcao -> Inimigo
inimigo5 posPortal direcao = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = 100
    , velocidadeInimigo = 1.8
    , ataqueInimigo = 15
    , butimInimigo = 45
    , projeteisInimigo = []
    }

listaTorresLoja :: Loja
listaTorresLoja = [(250, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 25
            , alcanceTorre = 2
            , rajadaTorre = 4
            , cicloTorre = 5
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Fogo
                , duracaoProjetil = Finita 5
                }
            }),
            (150, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 10
            , alcanceTorre = 2
            , rajadaTorre = 1
            , cicloTorre = 2
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Resina
                , duracaoProjetil = Finita 5
                }
            }),
            (200, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 15
            , alcanceTorre = 2
            , rajadaTorre = 1
            , cicloTorre = 2
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Gelo
                , duracaoProjetil = Finita 5
                }
            })]

mapaexemplo :: Mapa
mapaexemplo =  [[t, t, r, a, a, a],
                [r, t, r, a, r, r],
                [r, t, r, a, r, t],
                [r, t, r, a, r, t],
                [r, t, t, t, t, t],
                [a, a, a, a, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua

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

mapa02 :: Mapa
mapa02=[[r, r, r, t, a, a, r, r],
        [r, t, t, t, a, r, r, r],
        [r, t, r, r, a, r, r, r],
        [r, t, r, r, a, r, r, r],
        [r, t, r, t, t, t, t, t],
        [r, t, t, t, a, r, r, t],
        [a, a, a, a, a, r, r, t],
        [r, r, r, r, r, r, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua

mapa03 :: Mapa
mapa03=[[r, r, r, r, a, r, r, r],
        [t, t, t, t, a, r, r, r],
        [r, a, a, t, a, r, r, t],
        [r, a, r, t, t, t, r, t],
        [r, a, r, r, r, t, r, t],
        [r, a, r, r, r, t, r, t],
        [a, a, r, r, r, t, t, t],
        [r, r, r, r, r, r, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua
