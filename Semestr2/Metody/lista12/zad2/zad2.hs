import Data.List
import Control.Monad
perms1 :: Eq a => [a] -> [[a]]
perms1 [] = [[]]
perms1 xs = concatMap f xs where f x = map (x:) (perms1 $ delete x xs) 


perms2 :: Eq a => [a] -> [[a]]
perms2 [] = [[]]
perms2 xs = [x:ys | x <- xs, ys <- perms2 $ delete x xs] 


perms3 :: Eq a => [a] -> [[a]]

perms3 [] = return []
perms3 xs = do
	x <- xs
	ys <- perms3 $ delete x xs
	return (x:ys)
