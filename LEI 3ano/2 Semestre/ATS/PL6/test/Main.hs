module Main where

import Test.QuickCheck
import Test.QuickCheck.Function
import Data.List (find, reverse, product)
import MyLib

--------------------------------------------------------------------------------
-- Exercise 1: mulL Properties
--------------------------------------------------------------------------------

-- (a) Reversing the list returns the same result.
prop_mulL_reverse :: [Integer] -> Bool
prop_mulL_reverse l = mulL l == mulL (reverse l)

-- (b) A list with a single element returns that element as the result.
prop_mulL_single :: Integer -> Bool
prop_mulL_single x = mulL [x] == x

-- (c) The result is equal to the result of Haskell's built-in product function.
prop_mulL_product :: [Integer] -> Bool
prop_mulL_product l = mulL l == product l


--------------------------------------------------------------------------------
-- Exercise 2: Searching for an element
--------------------------------------------------------------------------------

-- Property verifying that find' behaves identically to standard find
-- Note: This is EXPECTED TO FAIL for the buggy 'find'' implementation.
prop_findBuggy_equiv :: Fun Integer Bool -> [Integer] -> Bool
prop_findBuggy_equiv (Fn f) l = find' f l == find f l

-- Property verifying that findCorrect behaves identically to standard find
-- This is EXPECTED TO PASS.
prop_findCorrect_equiv :: Fun Integer Bool -> [Integer] -> Bool
prop_findCorrect_equiv (Fn f) l = findCorrect f l == find f l


--------------------------------------------------------------------------------
-- Exercise 3: Implementation of f Properties
--------------------------------------------------------------------------------

-- (a) Implementation of f based on properties
-- (b) Identification of f as zip

-- property f1: null (f l1 []) && null (f [] l1)
prop_f1 :: [Int] -> Bool
prop_f1 l1 = null (fZip l1 []) && null (fZip [] l1)

-- property f2: length (f l1 l2) == min (length l1) (length l2)
prop_f2 :: [Int] -> [Char] -> Bool
prop_f2 l1 l2 = length (fZip l1 l2) == min (length l1) (length l2)

-- property f3: prefix properties
prop_f3_1 :: [Int] -> [Int] -> Property
prop_f3_1 l1 l2 = length l1 < length l2 ==> l1 == map fst (fZip l1 l2)

prop_f3_2 :: [Int] -> [Int] -> Property
prop_f3_2 l1 l2 = length l1 > length l2 ==> l2 == map snd (fZip l1 l2)

-- Comparison of fZip with standard zip
prop_f_zip_equiv :: [Int] -> [Char] -> Bool
prop_f_zip_equiv l1 l2 = fZip l1 l2 == zip l1 l2


--------------------------------------------------------------------------------
-- Execution
--------------------------------------------------------------------------------

main :: IO ()
main = do
  putStrLn "\n--- Exercise 1: mulL Properties (Fixed base case to 1) ---"
  quickCheck prop_mulL_reverse
  quickCheck prop_mulL_single
  quickCheck prop_mulL_product

  putStrLn "\n--- Exercise 2: Buggy find' Property (Will FAIL) ---"
  quickCheck prop_findBuggy_equiv

  putStrLn "\n--- Exercise 2: Correct findCorrect Property (Should PASS) ---"
  quickCheck prop_findCorrect_equiv

  putStrLn "\n--- Exercise 3: fProperties (zip) (Should PASS) ---"
  quickCheck prop_f1
  quickCheck prop_f2
  quickCheck prop_f3_1
  quickCheck prop_f3_2
  quickCheck prop_f_zip_equiv
