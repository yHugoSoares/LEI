{-|
Module:         Ficha 2
Description:    Ficha 2 de LI1
Copyright:      (C) Hugo Soares <hugoferreirasoares@gmail.com>, 2024
Stability:      In development
Portability:    POSIX

Este módulo contém definições Haskell para o cálculo de funções recursivas simples.
-}

module Ficha2 where
{-| Tipo de dados que representa movimentos no plano. -}
data Movimento = Norte | Sul | Este | Oeste deriving Show
{-| Tipo de dados de um ponto/coordenadas. -}
type Ponto = (Double, Double)

move :: Ponto -> Movimento -> Ponto
move (x,y) Norte = (x, y+1)
move (x,y) Sul = (x, y-1)
move (x,y) Este = (x+1, y)
move (x,y) Oeste = (x-1, y)

dist :: Ponto -> Ponto -> Double
dist (x1,y1) (x2,y2) = sqrt((x2-x1)^2 + (y2-y1)^2)

southest :: Ponto -> Ponto -> Ponto
southest (x1, y1) (x2, y2) = if y1 > y2 then (x2, y2) else (x1, y1)

move2 :: Ponto -> Double -> Movimento -> Ponto
move2 (x,y) size Norte = if y+1 > size then (x, y+1) else (x,y)
move2 (x,y) size Sul = if y-1 < 0 then (x, y-1) else (x,y)
move2 (x,y) size Este = if x+1 > size then (x+1, y) else (x,y)
move2 (x,y) size Oeste = if x-1 < 0 then (x-1, y) else (x,y)

alteraPonto :: Ponto -> Double -> Ponto -- (2,3) 3 = (2,0)
alteraPonto (x,y) tam 
    |   y-tam > 0 = (x,y-tam)
    |   otherwise = (x,y)

alteraCentro :: Ponto -> Double -> Ponto -- (2,1) 4 = (0, -1)
alteraCentro (x,y) tam
    |   xm < 0 || ym < 0 = (x,y)
    |   otherwise = (xm, ym)
        where (xm, ym) = (x - tam/2, y - tam/2)

type Velocidade = Double
type Tempo = Double

moveVelX :: Ponto -> Velocidade -> Tempo -> Ponto
moveVelX (x,y) vel time = (xf,y)
    where xf = x + (vel * time)

moveVelY :: Ponto -> Velocidade -> Tempo -> Ponto
moveVelY (x,y) vel time = (x,yf)
    where yf = y + (vel * time)

type VelDuplo = (Double, Double)

move2Eixos :: Ponto -> VelDuplo -> Tempo -> Ponto
move2Eixos (x,y) (vx,vy) t = (xf,yf)
    where (xf,yf) = (x+(vx*t),y+(vy*t))

data Figura = Circulo Ponto Double | Rectangulo Ponto Ponto | Quadrado Ponto Double deriving (Show,Eq)

isInside :: Ponto -> Figura -> Bool
isInside (x,y) (Circulo (cx,cy) tam) = dist (x,y) (cx,cy) <= tam
isInside (x,y) (Rectangulo (px1,py1) (px2,py2)) = x > xmax && x < xmin && y > ymax && y < ymin
    where 
        (xmax, ymax) = (max px1 px2,max py1 py2)
        (xmin, ymin) = (min px1 px2, min py1 py2)
isInside (x,y) (Quadrado (vx,vy) l) = x < vx && y < vy && x > xmin && y > ymin
    where (xmin, ymin) = (vx-l,vy-l)

menorQuadrado :: Figura -> Figura
menorQuadrado (Quadrado (x,y) l) = Quadrado (x,y) l
menorQuadrado (Circulo (x,y) r) = Quadrado (x-r,y+r) (2*r)
menorQuadrado (Rectangulo (x1,y1) (x2,y2)) = Quadrado (px, py) lado
    where 
        (px, py) = (min x1 x2, max y1 y2)
        lado = max (abs(x1-x2)) (abs(y1-y2))

maiorCirculo :: Figura -> Figura
maiorCirculo (Circulo (x,y) l) = Circulo (x,y) l
maiorCirculo (Quadrado (x,y) l) = Circulo (px,py) r
    where
        r = l/2
        (px,py) = (x + l/2, y - l/2)
maiorCirculo (Rectangulo (x1,y1) (x2,y2)) = Circulo (px,py) r
    where
        (px,py) = ((x1+x2)/2, (y1+y2)/2)
        r = dist (x1,y1) (x2,y2) / 2

contida :: Figura -> Figura -> Bool
contida (Circulo (x1,y1) r1) (Circulo (x2,y2) r2) = craio > r1
        where
            craio = dist (x2,y2) (x1+r1,y1+r1)
contida (Rectangulo (x1,y1) (x2,y2)) (Rectangulo (x3,y3) (x4,y4)) = (x1 > x3 && x1 > x4 && x2 < x3 && x2 < x4 && y1 > y3 && y1 > y4 && y2 < y3 && y2 < y4) 
    || (x1 < x3 && x1 < x4 && x2 > x3 && x2 > x4 && y1 < y3 && y1 < y4 && y2 > y3 && y2 > y4)
-- contida (Quadrado (x1,y1) l1) (Quadrado (x2,y2) l2) =
contida _ _ = False