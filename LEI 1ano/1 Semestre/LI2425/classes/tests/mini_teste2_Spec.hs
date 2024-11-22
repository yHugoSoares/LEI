module Mini_Teste2_Spec where
import Mini_Teste2 
import Test.HUnit

teste1 = "Teste f" ~: 4 ~=? f([1,2,3,4,5] 5)
teste2 = "Teste f" ~: 2 ~=? f([1,2,3,4,5] 3)

testes = test [teste1, teste2]