f :: [Integer] -> Integer -> Maybe Integer
f [] acc = Just(acc)
f (x:xs) acc 
	| x == 0 = Nothing
	| otherwise = f xs (x*acc)
prod :: [Integer] -> Integer
prod xs = case f xs 1 of
	Just n -> n
	Nothing -> 0 







