{-|
Module:         Mini_Teste3
Description:    Teste modelo 3 dos mini testes de LI1
Copyright:      (C) Hugo Soares <hugoferreirasoares@gmail.com>, 2024
Stability:      In development
Portability:    POSIX

Este módulo contém definições Haskell com Gloss.
-}
module Mini_Teste3 where
import Graphics.Gloss
import Graphics.Gloss.Interface.Pure.Game

-- Tipos do estado do jogo
type Coordenadas = (Float, Float)
type Velocidade = (Float, Float)
type Tempo = Float
type Estado = (Coordenadas, Velocidade, Tempo, [Coordenadas])

-- Estado inicial
estadoInicial :: Estado
estadoInicial = ((0, 0), (0.4, -0.8), 0, circulos)
    where 
        circulos = [(-20, 100), (50, -150), (150, 50), (-120, -120)]

-- Função para desenhar o estado
desenhaEstado :: Estado -> Picture
desenhaEstado ((x, y), (_, vy), t, circulos) =
    Pictures (figuraPrincipal : figurasCirculos ++ [tempo])
    where
        figuraPrincipal = translate x y $ color (if vy < 0 then red else green) $ circleSolid 20
        figurasCirculos = map (\(cx, cy) -> translate cx cy $ color blue $ circleSolid 15) circulos
        tempo = translate 150 150 $ scale 0.1 0.1 $ Text (show $ floor t)

-- Função para calcular a distância entre dois pontos
distancia :: Coordenadas -> Coordenadas -> Float
distancia (x1, y1) (x2, y2) = sqrt ((x2 - x1) ^ 2 + (y2 - y1) ^ 2)

-- Reage ao passar do tempo
reageTempo :: Float -> Estado -> Estado
reageTempo n ((x, y), (vx, vy), t, circulos) = ((x + vx', y + vy'), (vx', vy'), t + n, circulosAtualizados)
    where
        vy' = if y + vy <= (-190) || y + vy >= 190 then -vy else vy
        vx' = if x + vx <= (-190) || x + vx >= 190 then -vx else vx
        raioFigura = 20
        raioCirculo = 15
        circulosAtualizados = filter (\c -> distancia(x + vx', y + vy') c > fromIntegral (raioFigura + raioCirculo)) circulos

-- Reage a eventos do teclado
reageEvento :: Event -> Estado -> Estado
reageEvento (EventKey (SpecialKey KeyUp) Down _ _) ((x, y), v, t, circulos)    = ((x, y + 5), v, t, circulos)
reageEvento (EventKey (SpecialKey KeyDown) Down _ _) ((x, y), v, t, circulos)  = ((x, y - 5), v, t, circulos)
reageEvento (EventKey (SpecialKey KeyLeft) Down _ _) ((x, y), v, t, circulos)  = ((x - 5, y), v, t, circulos)
reageEvento (EventKey (SpecialKey KeyRight) Down _ _) ((x, y), v, t, circulos) = ((x + 5, y), v, t, circulos)
reageEvento _ s = s -- Ignora outros eventos

-- Configuração da janela
dm :: Display
dm = InWindow "Jogo Exemplo" -- título da janela
    (400, 400) -- dimensão da janela
    (200, 200) -- posição no ecrã

corFundo :: Color
corFundo = greyN 0.5

fr :: Int
fr = 50

-- Função principal
main :: IO ()
main = play dm -- janela onde irá decorrer o jogo
    corFundo -- cor do fundo da janela
    fr -- frame rate
    estadoInicial -- define estado inicial do jogo
    desenhaEstado -- desenha o estado do jogo
    reageEvento -- reage a um evento
    reageTempo -- reage ao passar do tempo
