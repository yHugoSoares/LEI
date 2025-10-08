import Data.Time.Format.ISO8601 (yearFormat)
-- Ficha 1 CP

mylength :: [a] -> Int
mylength [] = 0
mylength (x:xs) = 1 + mylength xs


myreverse :: [a] -> [a]
myreverse [] = []
myreverse (x:xs) = myreverse xs ++ [x]


mytake :: Int -> [a] -> [a]
mytake 0 _ = []
mytake _ [] = []
mytake n (x:xs) = x : mytake (n-1) xs

mymap :: (a -> b) -> [a] -> [b]
mymap _ [] = []
mymap f (x:xs) = f x : mymap f xs

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter _ [] = []
myfilter p (x:xs) | p x       = x : myfilter p xs
                    | otherwise = myfilter p xs

myuncurry :: (a -> b -> c) -> (a,b) -> c
myuncurry f (x,y) = f x y

mycurry :: ((a,b) -> c) -> a -> b -> c
mycurry f x y = f (x,y)

myflip :: (a -> b -> c) -> b -> a -> c
myflip f y x = f x y