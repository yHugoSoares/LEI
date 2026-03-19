module MyLib where

import Data.List (find)

--------------------------------------------------------------------------------
-- Exercise 1: mulL Properties
--------------------------------------------------------------------------------

-- | The original definition used 0 as the base case, which was a bug.
-- In multiplication, the identity element is 1.
mulL :: Num a => [a] -> a
mulL [] = 1
mulL (h : t) = h * mulL t


--------------------------------------------------------------------------------
-- Exercise 2: Searching for an element
--------------------------------------------------------------------------------

-- | Buggy implementation from the guide.
-- It searches from RIGHT to LEFT because it recurses before checking the head.
find' :: (a -> Bool) -> [a] -> Maybe a
find' _ [] = Nothing
find' f (x:xs) = case find' f xs of
                   Just k -> Just k
                   Nothing -> if f x then Just x else Nothing

-- | Correct implementation of find'.
-- It searches from LEFT to RIGHT, matching the standard Data.List.find.
findCorrect :: (a -> Bool) -> [a] -> Maybe a
findCorrect _ [] = Nothing
findCorrect f (x:xs) = if f x then Just x else findCorrect f xs


--------------------------------------------------------------------------------
-- Exercise 3: Identifying function f
--------------------------------------------------------------------------------

-- | Function f identified as 'zip' based on the provided properties.
-- prop_f1: null (f l1 []) && null (f [] l1)
-- prop_f2: length (f l1 l2) == min (length l1) (length l2)
-- prop_f3_1: length l1 < length l2 ==> l1 == map fst (f l1 l2)
-- prop_f3_2: length l1 > length l2 ==> l2 == map snd (f l1 l2)
fZip :: [a] -> [b] -> [(a, b)]
fZip (x:xs) (y:ys) = (x, y) : fZip xs ys
fZip _ _ = []
