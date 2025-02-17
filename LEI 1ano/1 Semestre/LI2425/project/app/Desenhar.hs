module Desenhar where

import Graphics.Gloss
import Text.Printf (printf)
import Debug.Trace (trace)
import Data.List (sortBy)
import Data.Ord (comparing)

import Tempo
import ImmutableTowers
import LI12425
import Tarefa2

desenha :: ImmutableTowers -> Picture
desenha it =
    case gameState it of
        TitleScreen -> desenhaMenu (head (imgs it))

        LevelScreen -> desenhaMenu (imgs it !! 1)

        MapScreen -> Pictures [ imgs it !! 6,
            Translate x_center y_center $
            Pictures [desenhaMapaNormal it],
            desenhaValores it]

        MapErrorScreen -> imgs it !! 3

        BuyScreen -> desenhaBuyScreen it

        PauseScreen -> desenhaPauseScreen it

        GameOverScreen -> desenhaGameOverScreen it
    where
        x_center = -(fromIntegral (length (head (mapaJogo (jogo it))) * round cellSize) / 2) + cellSize / 2
        y_center = -(fromIntegral (length (mapaJogo (jogo it)) * round cellSize) / 2) + cellSize / 2
         -- Calculam os pixeis necessários para fazer a translação do mapa para o centro da tela

-- | Função que desenha os menus
desenhaMenu :: Picture -> Picture
desenhaMenu img = img

-- | Função que desenha a tela de compra (NEED TO GET COST FROM DATA)
desenhaBuyScreen :: ImmutableTowers -> Picture -- Ajustar coordenadas
desenhaBuyScreen it = Pictures [imgs it !! 2
    ,Translate (-297) (-263) $ Color white $ Scale 0.2 0.2 $ Text (show (creditosBase (baseJogo (jogo it))))
    ,Translate (-285) (-135) $ Color white $ Scale 0.2 0.2 $ Text (show (fst (head (lojaJogo (jogo it)))))
    ,Translate (-35) (-135) $ Color white $ Scale 0.2 0.2 $ Text (show (fst (head (tail (lojaJogo (jogo it))))))
    ,Translate 215 (-135) $ Color white $ Scale 0.2 0.2 $ Text (show (fst (last (lojaJogo (jogo it)))))]

desenhaPauseScreen :: ImmutableTowers -> Picture
desenhaPauseScreen it = imgs it !! 27

desenhaValores :: ImmutableTowers -> Picture
desenhaValores it = Pictures
    [ Translate (-710) 328 $ Scale 0.2 0.2 $ Color white $ Text (printf "%.2f" (totalTime it))  -- Display total time
    , Translate (-710) 390 $ Scale 0.2 0.2 $ Color white $ Text (show (creditosBase (baseJogo (jogo it))))  -- Display credits
    , Translate (-710) 276 $ Scale 0.2 0.2 $ Color white $ Text (show (vidaBase (baseJogo (jogo it))))  -- Display base life
    ]

-- | Função que desenha o Mapa
desenhaMapaNormal :: ImmutableTowers -> Picture
desenhaMapaNormal it = Pictures (
    desenhaTerreno mapa images ++
    desenhaPortais mapa portais images ++
    desenhaBase base mapa images fs ++
    desenhaInimigos inimigos mapa images portais fs ++
    desenhaTorres torres (length mapa) images ++
    desenhaProjeteis (projeteisAtivos it) (length mapa) images ++
    maybe [] (\pos -> [desenhaSelecionado pos]) sSquare)
        where
            mapa = mapaJogo (jogo it)
            base = baseJogo (jogo it)
            portais = portaisJogo (jogo it)
            inimigos = inimigosJogo (jogo it)
            torres = torresJogo (jogo it)
            images = imgs it
            sSquare = selectedSquare it
            fs = fst (frameState it)

-- | Função que desenha o terreno do mapa
desenhaTerreno :: Mapa -> [Picture] -> [Picture]
desenhaTerreno mapa imgs =
    let largura = length (head mapa)
        altura = length mapa
        borda = [ Translate xPos yPos (imgs !! 10)
                | x <- [-1..largura]
                , let xPos = fromIntegral x * cellSize
                , y <- [-1, altura]
                , let yPos = fromIntegral y * cellSize
                ] ++
                [ Translate xPos yPos (imgs !! 10)
                | y <- [0..altura-1]
                , let yPos = fromIntegral y * cellSize
                , x <- [-1, largura]
                , let xPos = fromIntegral x * cellSize
                ]
    in borda ++
       [ Translate xPos yPos (desenhaCelulaNormal terreno imgs)
       | (y, linha) <- zip [0 :: Int ..] (reverse mapa)
       , (x, terreno) <- zip [0 :: Int ..] linha
       , let xPos = fromIntegral x * cellSize
       , let yPos = fromIntegral y * cellSize
       ]

-- | Função que desenha os portais
desenhaPortais :: Mapa -> [Portal] -> [Picture] -> [Picture]
desenhaPortais mapa portais imgs =
    [ Translate (x * cellSize) ((fromIntegral (length mapa) - y - 1) * cellSize) (imgs !! 11)
    | Portal { posicaoPortal = (x, y) } <- portais
    ]

-- | Função que desenha a base
desenhaBase :: Base -> Mapa -> [Picture] -> Int -> [Picture]
desenhaBase base mapa imgs fs = [
    Translate (fst (posicaoBase base) * cellSize) ((fromIntegral (length mapa) - snd (posicaoBase base) - 1) * cellSize) (imgs !! (12+fs)),
    Translate (-710) 400 $ Scale 0.2 0.2 $ Color white $ Text (show (vidaBase base)),
    Translate (-710) 300 $ Scale 0.2 0.2 $ Color white $ Text (show (creditosBase base))
    ]

-- | Função que desenha os inimigos
desenhaInimigos :: [Inimigo] -> Mapa -> [Picture] -> [Portal] -> Int -> [Picture]
desenhaInimigos inimigos mapa imgs portais fs =
    [ Translate (fst (posicaoInimigo i) * cellSize) ((fromIntegral (length mapa) - snd (posicaoInimigo i) - 1) * cellSize) (desenhaInimigo i imgs portais fs)
    | i <- ordprintinimigo inimigos
    ]

-- | Função que ordena os inimigos por y e x para desenhar sobreposição corretamente
ordprintinimigo :: [Inimigo] -> [Inimigo]
ordprintinimigo = sortBy (comparing (snd . posicaoInimigo) <> comparing (fst . posicaoInimigo))

desenhaInimigo :: Inimigo -> [Picture] -> [Portal] -> Int -> Picture
desenhaInimigo inimigo imgs portais fs = Pictures [inimigoPic, healthPic]
  where
    inimigoPic
      | isSpawning inimigo portais = imgs !! 17  -- Replace with the correct index for the spawning image
      | otherwise = case direcaoInimigo inimigo of
          Norte -> imgs !! (19+fs)  -- Replace with the correct index for the north-facing image
          Sul   -> imgs !! (21+fs)  -- Replace with the correct index for the south-facing image
          Este  -> imgs !! (23+fs)  -- Replace with the correct index for the east-facing image
          Oeste -> imgs !! (25+fs)  -- Replace with the correct index for the west-facing image
    healthPic = Translate (fst (posicaoInimigo inimigo) - 5) (10 + snd (posicaoInimigo inimigo)) $
                Scale 0.1 0.1 $ Color red $ Text (printf "%.1f" (vidaInimigo inimigo))
    isSpawning :: Inimigo -> [Portal] -> Bool
    isSpawning ini = any (\portal -> distancia (posicaoInimigo ini) (posicaoPortal portal) < 0.4)

-- | Função que desenha as torres
desenhaTorres :: [Torre] -> Int -> [Picture] -> [Picture]
desenhaTorres torres mapLength imgs =
    [ Translate (fst (posicaoTorre t) * cellSize) ((0.5 + fromIntegral mapLength - snd (posicaoTorre t) - 1) * cellSize) (desenhaTorre t imgs)
    | t <- ordprinttorre torres
    ]

-- | Função que ordena as torres por y para desenhar sobreposição corretamente
ordprinttorre :: [Torre] -> [Torre]
ordprinttorre = sortBy (comparing (snd . posicaoTorre))

-- | Função que desenha uma torre com base no tipo de projétil
desenhaTorre :: Torre -> [Picture] -> Picture
desenhaTorre torre imgs = case tipoProjetil (projetilTorre torre) of
    Fogo   -> imgs !! 14
    Resina -> imgs !! 15
    Gelo   -> imgs !! 16

-- | Function to draw the projectiles
desenhaProjeteis :: [ProjetilEmVoo] -> Int -> [Picture] -> [Picture]
desenhaProjeteis projeteis mapLength imgs =
    [ Translate (fst pos) ((fromIntegral mapLength - snd pos - 1) * cellSize) (desenhaProjetil (tipoProjetilEmVoo p) imgs)
    | p <- projeteis
    , let pos = lerp (posicaoInicial p) (posicaoFinal p) (1 - tempoRestante p / tempoTotal p)
    , trace (show pos) True  -- Debug print
    ]

-- | Function to draw a projectile based on its type
desenhaProjetil :: TipoProjetil -> [Picture] -> Picture
desenhaProjetil Fogo imgs = imgs !! 7  -- Replace with the correct index for fire projectile image
desenhaProjetil Resina imgs = imgs !! 8  -- Replace with the correct index for resin projectile image
desenhaProjetil Gelo imgs = imgs !! 9  -- Replace with the correct index for ice projectile image

-- | Função que desenha uma célula do mapa
desenhaCelulaNormal :: Terreno -> [Picture] -> Picture
desenhaCelulaNormal Terra imgs = imgs !! 9
desenhaCelulaNormal Relva imgs = imgs !! 8
desenhaCelulaNormal Agua  imgs = imgs !! 7

-- | Função que desenha a tela de Game Over
desenhaGameOverScreen :: ImmutableTowers -> Picture
desenhaGameOverScreen it
    | perdeuJogo (jogo it) = imgs it !! 4
    | otherwise = imgs it !! 5

-- | Função que desenha o quadrado selecionado
desenhaSelecionado :: Posicao -> Picture
desenhaSelecionado (x, y) = Translate x y $ Color (makeColorI 255 0 0 128) $ rectangleWire cellSize cellSize