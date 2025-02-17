module Main where

import Graphics.Gloss

import Desenhar
import Eventos
import ImmutableTowers
import Tempo

janela :: Display
janela = InWindow "Immutable Towers" (1600, 900) (0, 0)

fundo :: Color
fundo = black

fr :: Int
fr = 60

loadImages :: IO [Picture]
loadImages = do
    mainmenu <- loadBMP "bmp/mainmenu.bmp"
    levelmenu <- loadBMP "bmp/levelmenu.bmp"
    buymenu <- loadBMP "bmp/buymenu.bmp"
    mapError <- loadBMP "bmp/maperror.bmp"
    youlose <- loadBMP "bmp/youlose.bmp"
    youwin <- loadBMP "bmp/youwin.bmp"
    backmap <- loadBMP "bmp/backmap.bmp"
    pause <- loadBMP "bmp/pausemenu.bmp"
    agua <- loadBMP "bmp/Tiles/water.bmp"
    relva <- loadBMP "bmp/Tiles/grass.bmp"
    terra <- loadBMP "bmp/Tiles/dirt.bmp"
    border <- loadBMP "bmp/Tiles/border.bmp"
    portal <- loadBMP "bmp/Buildings/portal.bmp"
    base1 <- loadBMP "bmp/Buildings/base1.bmp"
    base2 <- loadBMP "bmp/Buildings/base2.bmp"
    tower_fire <- loadBMP "bmp/Buildings/tower_fire.bmp"
    -- projectile_fire <- loadBMP "bmp/Projectiles/projectile_fire.bmp"
    tower_resin <- loadBMP "bmp/Buildings/tower_resin.bmp"
    -- projectile_resin <- loadBMP "bmp/Projectiles/projectile_resin.bmp"
    tower_ice <- loadBMP "bmp/Buildings/tower_ice.bmp"
    -- projectile_ice <- loadBMP "bmp/Projectiles/projectile_ice.bmp"
    skeleton_spawn1 <- loadBMP "bmp/Enemies/skeletonSpawning1.bmp"
    skeleton_spawn2 <- loadBMP "bmp/Enemies/skeletonSpawning2.bmp"
    skeletonN1 <- loadBMP "bmp/Enemies/skeletonN1.bmp"
    skeletonN2 <- loadBMP "bmp/Enemies/skeletonN2.bmp"
    skeletonS1 <- loadBMP "bmp/Enemies/skeletonS1.bmp"
    skeletonS2 <- loadBMP "bmp/Enemies/skeletonS2.bmp"
    skeletonE1 <- loadBMP "bmp/Enemies/skeletonE1.bmp"
    skeletonE2 <- loadBMP "bmp/Enemies/skeletonE2.bmp"
    skeletonW1 <- loadBMP "bmp/Enemies/skeletonW1.bmp"
    skeletonW2 <- loadBMP "bmp/Enemies/skeletonW2.bmp"
    -- skeleton_spawn1_ice <- loadBMP "bmp/Enemies/skeletonSpawning1_ice.bmp"
    -- skeletonN1_ice <- loadBMP "bmp/Enemies/skeletonN1_ice.bmp"
    -- skeletonS1_ice <- loadBMP "bmp/Enemies/skeletonS1_ice.bmp"
    -- skeletonE1_ice <- loadBMP "bmp/Enemies/skeletonE1_ice.bmp"
    -- skeletonW1_ice <- loadBMP "bmp/Enemies/skeletonW1_ice.bmp"

    return [mainmenu, levelmenu, buymenu, mapError, youlose, youwin, backmap,
            agua, relva, terra, border,
            portal, base1, base2, tower_fire, tower_resin, tower_ice,
            skeleton_spawn1,skeleton_spawn2,skeletonN1,skeletonN2,skeletonS1,skeletonS2,skeletonE1,skeletonE2,skeletonW1,skeletonW2, pause]
            -- projectile_fire, projectile_resin, projectile_ice]

main :: IO ()
main = do
    imgs <- loadImages

    let initialState = initialStateMap1 imgs
            
    play janela fundo fr initialState desenha reageEventos reageTempo
