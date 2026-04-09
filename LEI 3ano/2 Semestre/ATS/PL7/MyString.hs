
import Test.QuickCheck

import Data.List


data MyString = MyString [(Char,Int)] 
       deriving Show


braga :: MyString
braga = MyString [('a',3),('g',4),('r',2) ,('B',1),('a',5)] 


-- MyString Equality: equal lengths (ensuring no duplicated indices) 
--                    and, for each index the chars are the same
eqMyString :: MyString -> MyString -> Bool
eqMyString (MyString l1) (MyString l2)
            | length l1 == length l2 = and [ pos i l1 == pos i l2
                                           |  i <- [1..length l1]
                                           ] 
            | otherwise       = False
  where   pos :: Int -> [(Char,Int)] -> Maybe Char 
          pos _ [] = Nothing
          pos i ((c,x):ls) = if i == x then Just c else pos i ls


instance Eq MyString where
    (==) = eqMyString


toString :: MyString -> String
toString (MyString l) =  map fst (sortOn snd l)

fromString :: String -> MyString
fromString s = MyString (zip s [1..])


-- Round trip properties

prop_FromTo :: String -> Bool
prop_FromTo s = toString (fromString s) == s

prop_ToFrom :: MyString -> Bool
prop_ToFrom l =  fromString (toString l) == l


-- Generator needed to produce random MyString values

genMyString :: Gen MyString
genMyString = do  s <- arbitrary
                  let l = zip s [1..]
                  l' <- shuffle l
                  return (MyString l')

-- We define the shrink to produce nicer counterexamples:
-- we aply the shrink of strings and we use map to produce a list of MyString

instance Arbitrary MyString where
     arbitrary = genMyString 
     shrink (MyString s) = map MyString (shrink s)

