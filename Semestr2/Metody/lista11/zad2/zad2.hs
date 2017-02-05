ssm :: Ord a => [a] -> [a]
ssm [] = []
ssm (x:xs) = reverse $ foldl ssm1 [x] xs


ssm1 :: Ord a => [a] -> a -> [a]
ssm1 (x:xs) n 
	| n > x = n:x:xs
	| otherwise = x:xs
	

