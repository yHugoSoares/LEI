module Sinh where

-- PROBLEMA 2: Seno Hiperbólico via Série de Taylor

-- Versão conforme enunciado (CORRETA)
sinh_approx :: Floating a => a -> Int -> a
sinh_approx x = wrapper . worker
  where
    wrapper = head
    
    worker :: Floating a => Int -> [a]
    worker 0 = start x
    worker n = loop x (worker (n-1))
    
    -- Estado: [soma, numerador_atual, denom1, denom2, incremento]
    loop :: Floating a => a -> [a] -> [a]
    loop x [s, h, k, j, m] = 
      [h/k + s,      -- adiciona termo atual (h/k) à soma
       x^2 * h,      -- próximo numerador
       k * j,        -- próximo denominador completo
       j + m,        -- atualiza j
       m + 8]        -- atualiza incremento
    
    start :: Floating a => a -> [a]
    start x = 
      [x,      -- s₀: primeiro termo x^1/1! = x
       x^3,    -- h₀: x^3 (para calcular segundo termo)
       6,      -- k₀: 6 = 2*3 (denominador do segundo termo)
       20,     -- j₀: próximo multiplicador
       22]     -- m₀: incremento inicial

-- Testes para verificar correção
test_sinh :: IO ()
test_sinh = do
  let x = 1.0
  putStrLn "=== Teste sinh(1.0) ==="
  putStrLn $ "n=0:  " ++ show (sinh_approx x 0)
  putStrLn $ "n=1:  " ++ show (sinh_approx x 1)
  putStrLn $ "n=2:  " ++ show (sinh_approx x 2)
  putStrLn $ "n=3:  " ++ show (sinh_approx x 3)
  putStrLn $ "n=5:  " ++ show (sinh_approx x 5)
  putStrLn $ "n=10: " ++ show (sinh_approx x 10)
  putStrLn $ "Exato: " ++ show (sinh x)
  putStrLn ""
  
  let x2 = 0.5
  putStrLn "=== Teste sinh(0.5) ==="
  putStrLn $ "n=5:  " ++ show (sinh_approx x2 5)
  putStrLn $ "Exato: " ++ show (sinh x2)
  putStrLn ""
  
  -- Mostrar evolução do estado
  putStrLn "=== Evolução do estado para x=1 ==="
  let states = take 4 $ iterate (loop_debug 1.0) (start_debug 1.0)
  mapM_ print_state $ zip [0..] states

-- Versões para debug
start_debug :: Floating a => a -> [a]
start_debug x = [x, x^3, 6, 20, 22]

loop_debug :: Floating a => a -> [a] -> [a]
loop_debug x [s, h, k, j, m] = [h/k + s, x^2 * h, k * j, j + m, m + 8]

print_state :: (Int, [Double]) -> IO ()
print_state (n, [s, h, k, j, m]) = do
  putStrLn $ "Estado " ++ show n ++ ":"
  putStrLn $ "  soma = " ++ show s
  putStrLn $ "  h = " ++ show h ++ ", k = " ++ show k
  putStrLn $ "  j = " ++ show j ++ ", m = " ++ show m
  putStrLn $ "  termo atual = " ++ show (h/k)
  putStrLn ""