class Monoidd a where
	(***) :: a -> a -> a
	e :: a
	infixl 6 ***
	infixr 7 ^^^
	(^^^) :: Monoidd a => a -> Integer -> a
	a ^^^ 0 = e
	a ^^^ n 
		| n `mod` 2 == 0 = a^^^(n `div` 2) *** a^^^(n `div` 2)
		| otherwise = a^^^(n `div` 2) *** a^^^(n `div` 2) *** a

data Mtx a = Mtx a a a a

instance (Num a) => Monoidd (Mtx a) where
	e = Mtx 1 0 0 1
	(***) = mult where
		mult (Mtx a11 a12 a21 a22) (Mtx b11 b12 b21 b22) = 
			Mtx (a11*b11 + a12*b21) (a11*b12 + a12*b22) (a21*b11 + a22*b21) (a21*b12 + a22*b22)

getfib :: Mtx a -> a
getfib (Mtx _ b _ _) = b

fib :: Integer -> Integer
fib n = getfib ((Mtx 0.0 1.0 1.0 1.0)^^^n) 
