sublists1 :: [a] -> [[a]]
sublists1 [] = [[]]
sublists1 (x:xs) = map (x:) (sublists1 xs) ++ sublists1 xs

sublists2 :: [a] -> [[a]]
sublists2 [] = [[]]
sublists2 (x:xs) = [x:ys | ys<-sublists2 xs] ++ [ys | ys <- sublists2 xs]

sublists3 :: [a] -> [[a]]
sublists3 [] = return []
sublists3 (x:xs) = do
	ys <- sublists3 xs
	result <- [x:ys, ys]
	return result