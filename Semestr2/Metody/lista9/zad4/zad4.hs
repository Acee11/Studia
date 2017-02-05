fibbonaci :: Integer -> Integer -> Integer -> Integer

fibbonaci x _ 0 = x
fibbonaci _ y 1 = y
fibbonaci x y z = fibbonaci y (x+y) (z-1)

fib :: Integer -> Integer
fib = fibbonaci 1 1