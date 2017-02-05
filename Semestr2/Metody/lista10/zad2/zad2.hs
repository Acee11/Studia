halve :: [a] -> ([a],[a])
merge :: Ord a => ([a],[a]) -> [a]
cross :: (a -> c, b -> d) -> (a,b) -> (c,d)
pair :: (a -> b, a -> c) -> a -> (b,c)

pair (f,g) x = (f x, g x)

cross (f,g) = pair(f.fst, g.snd)

halve a = (take n a, drop n a) where n = (length a) `div` 2

merge (xs, []) = xs
merge ([], xs) = xs
merge ((x:xs), (y:ys)) 
	| x < y = x:merge (xs, (y:ys))
	| otherwise = y:merge ((x:xs), ys)

msort [] = []
msort [x] = [x]
msort xs = merge.cross(msort, msort).halve $ xs
