-- Ficha 1 CP

mylength :: [a] -> int
mylength [] = 0
mylength (x:xs) = 1 + mylength xs


myreverse :: [a] -> [a]
myreverse [] = []
myreverse (x:xs) = myreverse xs ++ [x]


mytake :: int -> [a] -> [a]
mytake 0 _ = []
mytake _ [] = []
mytake n (x:xs) = x : mytake (n-1) xs

