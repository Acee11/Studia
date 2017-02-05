newtype FSet a = FSet (a -> Bool)

empty :: FSet a
empty = FSet (\ _ -> False)

singleton :: Ord a => a -> FSet a
singleton x = FSet (\a -> if a == x then True else False)

fromList :: Ord a => [a] -> FSet a
fromList l = FSet (\x -> elem x l)

union :: Ord a => FSet a -> FSet a -> FSet a
union (FSet a) (FSet b) = FSet (\x -> a x || b x)

intersection :: Ord a => FSet a -> FSet a -> FSet a
intersection (FSet a) (FSet b) = FSet (\x -> a x && b x)

member :: Ord a => a -> FSet a -> Bool
member a (FSet b) = b a



