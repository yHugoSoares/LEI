module Eventos where

import Graphics.Gloss.Interface.Pure.Game
import ImmutableTowers
import Data.Maybe
import LI12425
import Tarefa1
import System.Exit (exitSuccess)
import System.IO.Unsafe (unsafePerformIO)

reageEventos :: Event -> ImmutableTowers -> ImmutableTowers
reageEventos (EventKey (SpecialKey KeyEnter) Down _ _) it =
    case gameState it of
        TitleScreen -> if validaJogo (jogo it)
            then it { gameState = MapScreen }
            else it { gameState = MapErrorScreen }
        MapErrorScreen -> it { gameState = TitleScreen }
        _ -> it -- Ignorar Enter nos outros estados

reageEventos (EventKey (Char 'b') Down _ _) it =
    case gameState it of
        MapScreen -> it { gameState = BuyScreen }
        BuyScreen -> it { gameState = MapScreen }
        _ -> it -- Ignorar 'B' nos outros estados

reageEventos (EventKey (Char 'p') Down _ _) it =
    case gameState it of
        MapScreen -> it { gameState = PauseScreen }
        PauseScreen -> it { gameState = MapScreen }
        BuyScreen -> it { gameState = MapScreen }
        _ -> it -- Ignorar 'Esc' nos outros estados

reageEventos (EventKey (MouseButton LeftButton) Down _ (x, y)) it =
    case gameState it of
        TitleScreen -> handleTitleScreenClick (x, y) it
        LevelScreen -> handleLevelScreenClick (x, y) it
        BuyScreen -> handleBuyScreenClick (x, y) it
        PauseScreen -> handlePauseScreenClick (x, y) it
        MapScreen -> handleMapScreenClick (x, y) it
        _ -> it -- Ignorar cliques nos outros estados

reageEventos _ it = it -- Ignorar outros eventos

handleTitleScreenClick :: (Float, Float) -> ImmutableTowers -> ImmutableTowers
handleTitleScreenClick (x, y) it
    | x >= -100 && x <= 100 && y >= -27 && y <= 27 = if validaJogo (jogo it) -- "Iniciar" button
        then it { gameState = MapScreen }
        else it { gameState = MapErrorScreen }
    | x >= -100 && x <= 100 && y >= -104 && y <= -50 = it { gameState = LevelScreen } -- "Niveis" button
    | x >= -100 && x <= 100 && y >= -179 && y <= -125 = unsafePerformIO exitSuccess `seq` it -- "Sair" button
    | otherwise = it

handleLevelScreenClick :: (Float, Float) -> ImmutableTowers -> ImmutableTowers
handleLevelScreenClick (x, y) it
    | x >= -100 && x <= 100 && y >= -27 && y <= 27 = (initialStateMap1 (imgs it)) { gameState = TitleScreen } -- "Level 1" button
    | x >= -100 && x <= 100 && y >= -104 && y <= -50 = (initialStateMap2 (imgs it)) { gameState = TitleScreen } -- "Level 2" button
    | x >= -100 && x <= 100 && y >= -179 && y <= -125 = (initialStateMap3 (imgs it)) { gameState = TitleScreen } -- "Level 3" button
    | otherwise = it

handleBuyScreenClick :: (Float, Float) -> ImmutableTowers -> ImmutableTowers
handleBuyScreenClick (x, y) it
    | x >= 375 && x <= 435 && y >= 198 && y <= 258 = it {gameState = MapScreen}
    | x >= -325 && x <= -175 && y >= -100 && y <= 50 = buyTower 0 it
    | x >= -75 && x <= 75 && y >= -100 && y <= 50 = buyTower 1 it
    | x >= 175 && x <= 325 && y >= -100 && y <= 50 = buyTower 2 it
    | otherwise = it

buyTower :: Int -> ImmutableTowers -> ImmutableTowers
buyTower index it =
    let (_, tower) = lojaJogo (jogo it) !! index
    in it { torreComprada = Just tower, gameState = MapScreen }

handlePauseScreenClick :: (Float, Float) -> ImmutableTowers -> ImmutableTowers
handlePauseScreenClick (x, y) it
    | x >= -100 && x <= 100 && y >= 165 && y <= 180 = it { gameState = MapScreen } -- "Resume" button
    | x >= -100 && x <= 100 && y >= -30 && y <= 30 = it { gameState = TitleScreen } -- "Title Screen" button
    | x >= -100 && x <= 100 && y >= -180 && y <= -165 = unsafePerformIO exitSuccess `seq` it -- "Quit" button
    | otherwise = it

handleMapScreenClick :: (Float, Float) -> ImmutableTowers -> ImmutableTowers
handleMapScreenClick (x, y) it =
    let (mx, my) = ((x + x_center) / cellSize, (y + y_center) / cellSize)
        selectedPos = (cellSize * fromIntegral (floor mx::Int), cellSize * fromIntegral (floor my::Int))
    in if isJust (torreComprada it)
        then placeTower (fromInteger (floor ((x + 256) / cellSize)),fromInteger (floor (8-((y + 256) / cellSize)))) it
        else it { selectedSquare = Just selectedPos }
        where
            x_center = fromIntegral (length (head (mapaJogo (jogo it))) * round cellSize) / 2
            y_center = fromIntegral (length (mapaJogo (jogo it)) * round cellSize) / 2

placeTower :: Posicao -> ImmutableTowers -> ImmutableTowers
placeTower pos it =
    let tower = fromJust (torreComprada it)
        updatedTower = tower { posicaoTorre = pos }
        existingTowers = torresJogo (jogo it)
        mapa = mapaJogo (jogo it)
        credits = creditosBase (baseJogo (jogo it))
        cost = fst $ head $ filter (\(_, t) -> projetilTorre t == projetilTorre tower) (lojaJogo (jogo it))
    in if terrenoEm pos mapa == Relva && not (any (\t -> posicaoTorre t == pos) existingTowers) && credits >= cost
        then it { jogo = (jogo it) { torresJogo = updatedTower : existingTowers
                                   , baseJogo = (baseJogo (jogo it)) { creditosBase = credits - cost } }
                , torreComprada = Nothing
                , selectedSquare = Nothing }
        else it -- Invalid position or not enough credits, do nothing