module Mini_Teste2_Spec where

import Mini_Teste3 -- Ensure this module exists and is correctly named
import Test.HUnit

isInsideWindow :: Coordenadas -> Bool
isInsideWindow (x, y) = x >= -190 && x <= 190 && y >= -190 && y <= 190