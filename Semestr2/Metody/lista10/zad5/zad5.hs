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

{-
instance Monoidd Integer where
	(***) = (\x -> (\y-> (x*y) `mod` 9876543210))
	e =  1
-}
instance Monoidd Integer where
	(***) = (+)
	e =  0
