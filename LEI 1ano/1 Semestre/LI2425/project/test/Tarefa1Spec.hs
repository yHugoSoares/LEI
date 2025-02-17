
module Tarefa1Spec (testesTarefa1) where

import Test.HUnit
import LI12425
import Tarefa1

-- Supondo que a função validaJogo tenha a seguinte assinatura:
-- validaJogo :: Jogo -> Bool

testesTarefa1 :: Test
testesTarefa1 =
  TestLabel "Testes Tarefa 1" $
    test
      [ "validaJogo - jogo válido" ~: True ~=? validaJogo
        (Jogo baseValida portalValido torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - portal inválido(não existe nenhum)" ~: False ~=? validaJogo 
        (Jogo baseValida portalInvalido1 torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - portal inválido(posição não em terra)" ~: False ~=? validaJogo 
        (Jogo baseValida portalInvalidoTerra torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - portal inválido(sobre a base)" ~: False ~=? validaJogo 
        (Jogo baseValida portalInvalidoSobreBase torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - portal inválido(mais de uma onda)" ~: False ~=? validaJogo 
        (Jogo baseValida portalInvalidoDuasOndas torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - inimigo inválido(inimigo com coordenadas diferentes)" ~: False ~=? validaJogo 
        (Jogo baseValida portalInvalidoInimigoCordsDiferentes torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - inimigo inválido(velocidade negativa)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreValida mapa01 inimigoInvalidoVelNegativa lojaValida),
        "validaJogo - inimigo inválido(vida negativa)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreValida mapa01 inimigoInvalidoVidaNegativa lojaValida),
        "validaJogo - inimigo inválido(projetil opostos)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreValida mapa01 inimigoInvalidoProjeiteisOpostos lojaValida),
        "validaJogo - torre inválida(sem sobre relva)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreInvalidaSemSobreRelva mapa01 inimigoValido lojaValida),
        "validaJogo - torre inválida(alcance negativo)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreInvalidaAlcanceNegativo mapa01 inimigoValido lojaValida),
        "validaJogo - torre inválida(rajada negativa)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreInvalidaRajadaNegativa mapa01 inimigoValido lojaValida),
        "validaJogo - torre inválida(ciclo negativo)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreInvalidaCicloNegativo mapa01 inimigoValido lojaValida),
        "validaJogo - torre inválida(tempo negativo)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreInvalidaTempoNegativo mapa01 inimigoValido lojaValida),
        "validaJogo - torre inválida(sobrepostas)" ~: False ~=? validaJogo
        (Jogo baseValida portalValido torreInvalidaSobrepostas mapa01 inimigoValido lojaValida),
        "validaJogo - base inválida(sem sobre terra)" ~: False ~=? validaJogo
        (Jogo baseInvalidaSemSobreTerra portalValido torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - base inválida(vida negativa)" ~: False ~=? validaJogo
        (Jogo baseInvalidaVidaNegativa portalValido torreValida mapa01 inimigoValido lojaValida),
        "validaJogo - mapa inválido" ~: False ~=? validaJogo 
        (Jogo baseValida portalValido torreValida mapa02 inimigoValido lojaValida)
      ]

portalValido :: [Portal]
portalValido = [
      Portal { posicaoPortal = (7, 2)
              ,ondasPortal = [Onda
                            { inimigosOnda = [inimigo1 (7, 2) Oeste 1 1 [], inimigo1 (7, 2) Oeste 1 1 []]
                            , cicloOnda = 1
                            , tempoOnda = 5
                            , entradaOnda = 5}]
                            }]

portalInvalidoTerra :: [Portal]
portalInvalidoTerra = 
      [Portal { posicaoPortal = (7, 0)
              ,ondasPortal = [Onda
                            { inimigosOnda = [inimigo1 (7, 2) Oeste 1 1 [], inimigo1 (7, 2) Oeste 1 1 []]
                            , cicloOnda = 1
                            , tempoOnda = 5
                            , entradaOnda = 5}]
                            }]

portalInvalidoSobreBase :: [Portal]
portalInvalidoSobreBase = 
      [Portal { posicaoPortal = (0, 0)
              ,ondasPortal = [Onda
                            { inimigosOnda = [inimigo1 (7, 2) Oeste 1 1 [], inimigo1 (7, 2) Oeste 1 1 []]
                            , cicloOnda = 1
                            , tempoOnda = 5
                            , entradaOnda = 5}]
                            }]

portalInvalidoDuasOndas :: [Portal]
portalInvalidoDuasOndas = 
      [Portal { posicaoPortal = (0, 0)
              ,ondasPortal = [Onda
                            { inimigosOnda = [inimigo1 (7, 2) Oeste 1 1 [], inimigo1 (7, 2) Oeste 1 1 []]
                            , cicloOnda = 1
                            , tempoOnda = 5
                            , entradaOnda = 5},
                            Onda
                            { inimigosOnda = [inimigo1 (7, 2) Oeste 1 1 [], inimigo1 (7, 2) Oeste 1 1 []]
                            , cicloOnda = 1
                            , tempoOnda = 5
                            , entradaOnda = 5}]
                            }]

portalInvalidoInimigoCordsDiferentes :: [Portal]
portalInvalidoInimigoCordsDiferentes = 
      [Portal { posicaoPortal = (0, 0)
              ,ondasPortal = [Onda
                            { inimigosOnda = [inimigo1 (7, 2) Oeste 1 1 [], inimigo1 (7, 0) Oeste (-1) 1 []]
                            , cicloOnda = 1
                            , tempoOnda = 5
                            , entradaOnda = 5}]
                            }]

inimigoValido :: [Inimigo]
inimigoValido = []

inimigoInvalidoVelNegativa :: [Inimigo]
inimigoInvalidoVelNegativa = [inimigo1 (7, 2) Oeste (-1) 1 []]

inimigoInvalidoVidaNegativa :: [Inimigo]
inimigoInvalidoVidaNegativa = [inimigo1 (7, 2) Oeste 1 (-1) []]

inimigoInvalidoProjeiteisOpostos :: [Inimigo]
inimigoInvalidoProjeiteisOpostos = [inimigo1 (7, 2) Oeste 1 1 [Projetil { tipoProjetil = Fogo, duracaoProjetil = Finita 5 }, Projetil { tipoProjetil = Gelo, duracaoProjetil = Finita 5 }]]

inimigo1 :: Posicao -> Direcao -> Float -> Float -> [Projetil] -> Inimigo
inimigo1 posPortal direcao vida velocidade projeteis = Inimigo
    { posicaoInimigo = posPortal
    , direcaoInimigo = direcao
    , vidaInimigo = vida
    , velocidadeInimigo = velocidade
    , ataqueInimigo = 15
    , butimInimigo = 50
    , projeteisInimigo = projeteis
    }

portalInvalido1 :: [Portal]
portalInvalido1 = []

torreValida :: [Torre]
torreValida = []

torreInvalidaSemSobreRelva :: [Torre]
torreInvalidaSemSobreRelva = [Torre { posicaoTorre = (0, 0)
            , danoTorre = 10
            , alcanceTorre = 2
            , rajadaTorre = 1
            , cicloTorre = 1
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Fogo
                , duracaoProjetil = Finita 5
                }
            }]

torreInvalidaAlcanceNegativo :: [Torre]
torreInvalidaAlcanceNegativo = [torre1 (0, 0) 10 (-2) 1 1 1]

torreInvalidaRajadaNegativa :: [Torre]
torreInvalidaRajadaNegativa = [torre1 (0, 0) 10 2 (-1) 1 1]

torreInvalidaCicloNegativo :: [Torre]
torreInvalidaCicloNegativo = [torre1 (0, 0) 10 2 1 (-1) 1]

torreInvalidaTempoNegativo :: [Torre]
torreInvalidaTempoNegativo = [torre1 (0, 0) 10 2 1 1 (-1)]

torreInvalidaSobrepostas :: [Torre]
torreInvalidaSobrepostas = [torre1 (0, 0) 10 2 1 1 1, torre1 (0, 0) 10 2 1 1 1]

torre1 :: Posicao -> Float -> Float -> Int -> Float -> Float -> Torre
torre1 pos dano alcance rajada ciclo tempo = Torre
            { posicaoTorre = pos
            , danoTorre = dano
            , alcanceTorre = alcance
            , rajadaTorre = rajada
            , cicloTorre = ciclo
            , tempoTorre = tempo
            , projetilTorre = Projetil
                { tipoProjetil = Fogo
                , duracaoProjetil = Finita 5
                }
            }
  
baseValida :: Base
baseValida = Base { vidaBase = 100
            , posicaoBase = (0, 0)
            , creditosBase = 1000 }

baseInvalidaSemSobreTerra :: Base
baseInvalidaSemSobreTerra = Base { vidaBase = 100
            , posicaoBase = (7, 7)
            , creditosBase = 1000 }

baseInvalidaVidaNegativa :: Base
baseInvalidaVidaNegativa = Base { vidaBase = -100
            , posicaoBase = (0, 0)
            , creditosBase = 1000 }

lojaValida :: Loja
lojaValida = [(250, Torre
            { posicaoTorre = (2, 0)
            , danoTorre = 10
            , alcanceTorre = 2
            , rajadaTorre = 1
            , cicloTorre = 1
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
            , cicloTorre = 1
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
            , rajadaTorre = 1
            , cicloTorre = 1
            , tempoTorre = 1
            , projetilTorre = Projetil
                { tipoProjetil = Gelo
                , duracaoProjetil = Finita 5
                }
            })]

mapa01 :: Mapa -- Valido
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

mapa02 :: Mapa  -- Não existe caminho entre a base e o portal
mapa02=[[t, t, r, r, a, a, a, r],
        [r, t, r, r, a, r, r, r],
        [r, t, r, r, a, r, t, t],
        [r, r, r, r, a, r, t, r],
        [r, t, r, r, a, r, t, r],
        [r, t, t, t, t, t, t, r],
        [r, r, r, r, a, r, r, r],
        [r, r, r, a, a, r, r, r]]
    where
        t = Terra
        r = Relva
        a = Agua