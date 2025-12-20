module Ex1 where

import BTree
import Cp
import List

-- 1.
-- Breadth-first traversal using catamorphism
bfsLevels :: BTree a -> [a]
bfsLevels = concat . levels

levels :: BTree a -> [[a]]
levels = cataBTree gene
  where
    gene = either (const []) buildLevel
    buildLevel (a, (l, r)) = [a] : zipWithDefault (++) l r
    
    zipWithDefault :: (a -> a -> a) -> [a] -> [a] -> [a]
    zipWithDefault f [] [] = []
    zipWithDefault f xs [] = xs
    zipWithDefault f [] ys = ys
    zipWithDefault f (x:xs) (y:ys) = f x y : zipWithDefault f xs ys


-- 2.
-- Breadth-first traversal using anamorphism
bft :: BTree a -> [a]
bft t = anaList coalg [t]
  where
    coalg [] = i1 ()
    coalg (Empty : ts) = coalg ts
    coalg (Node(a, (l, r)) : ts) = i2 (a, ts ++ [l, r])