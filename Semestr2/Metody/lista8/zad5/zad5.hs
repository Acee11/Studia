f :: Integer -> Integer
f x = x + 1

g :: Integer -> Integer
g x = 2 * x

pair :: ((a -> b),(a -> c)) -> a -> (b,c)
pair (f,g) x = (f x, g x)
