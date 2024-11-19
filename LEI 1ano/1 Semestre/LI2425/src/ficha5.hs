module Main where

import Graphics.Gloss
import Graphics.Gloss.Interface.Pure.Game

type Time = Float
data State = State Time Color (Float, Float)

baseColor = rose
imageSize = 30
movSize = 10
windowSize = (1600,900)
colorsCycle = [greyN 0.5, black, white, red, green, blue, yellow, cyan, magenta, rose, violet, azure, aquamarine, chartreuse, orange]

main :: IO ()
main = play
    displayMode
    backgroundColor
    10
    (State 0 baseColor (0,0))
    drawState
    eventReaction
    timeReaction
    where
        displayMode = InWindow "Ficha 5" windowSize (10, 10)
        backgroundColor = aquamarine

drawState (State t colour (x,y)) = Pictures [ 
    Translate x y $ color colour $ if t > 10 
        then rectangleSolid imageSize imageSize 
        else circleSolid imageSize,
    Translate (-700) 370 (Scale 0.3 0.3 $ Text ("Use WASD to move || Time: " ++ show t))
    ]
        
eventReaction :: Event -> State -> State
eventReaction (EventKey (Char c) Down _ _) (State t color (x, y))
    | c == 'a' && isInsideWindow (x - movSize, y) = State 0 black (x - movSize, y)
    | c == 'd' && isInsideWindow (x + movSize, y) = State 0 yellow (x + movSize, y)
    | c == 'w' && isInsideWindow (x, y + movSize) = State 0 red (x, y + movSize)
    | c == 's' && isInsideWindow (x, y - movSize) = State 0 rose (x, y - movSize)
eventReaction _ state = state

timeReaction dt (State t color pos) = State (t + dt) (nextColor (t + dt)) pos

nextColor t = colorsCycle !! (floor t `mod` length colorsCycle)


isInsideWindow :: (Float,Float) -> Bool
isInsideWindow (x,y) =  
    x > -(800 - imageSize) && x < (800 - imageSize) && 
    y > -(450 - imageSize) && y < (450 - imageSize)
