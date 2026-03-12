import Test.HUnit
import Data.List

type MyString = [(Char, Int)]

braga :: MyString
braga = [('a',5), ('r',2), ('a',3), ('B',1), ('g', 4)]

toString :: MyString -> String
toString l = map fst (sortOn snd l)

testtoString :: Test
testtoString = TestList
                [ "empty list"           ~: toString[]         ~?= ""
                , "singleton list"        ~: toString[('A', 1)] ~?= "A"
                , "multiple elems"        ~: toString braga     ~?= "Braga"
                ]
                

fromString :: String -> MyString
fromString s = zip s [1..]


testfromString :: Test
testfromString = TestList
		[ "empty list"		~: fromString []	~?= []
		, "singleton list"	~: fromString "d"	~?= [('d',1)]
		, "multiple elems"	~: fromString "ab"	~?= [('a',1), ('b',2)]
		]
