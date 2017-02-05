permi1 :: [a] -> [[a]]
permi1 [] = [[]]
permi1 (x:xs) = concatMap (insert1 x) (permi1 xs)

permi2 :: [a] -> [[a]]
permi2 [] = [[]]
permi2 (x:xs) = [ys | ys <- concatMap (insert1 x) (permi2 xs)]

permi3 :: [a] -> [[a]]
permi3 [] = return []
permi3 (x:xs) = do
	ys <- concatMap (insert1 x) (permi3 xs)
	return ys

insert1 :: a -> [a] -> [[a]]
insert1 x [] = [[x]]
insert1 x xs = map f [0..(length xs)]  where
	f i = first ++ (x:second) where (first,second) = splitAt i xs 
