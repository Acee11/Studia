merge :: Ord a => ([a],[a]) -> [a]
merge (xs, []) = xs
merge ([], xs) = xs
merge ((x:xs), (y:ys)) 
	| x < y = x:merge (xs, (y:ys))
	| otherwise = y:merge ((x:xs), ys)

msortn :: (Ord a) => [a] -> Int -> [a]
msortn _ 0 = []
msortn (x:_) 1 = [x]
msortn xs n = merge ((msortn (take k xs) k), (msortn (drop k xs) (n-k))) where
	k = n `div` 2	