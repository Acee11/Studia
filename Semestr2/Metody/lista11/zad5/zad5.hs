length1 :: [a] -> Integer
length1 xs = foldr (\_ y -> 1 + y) 0 xs 

length2 :: [a] -> Integer
length2 xs = foldl (\x -> \_ -> x + 1) 0 xs

(+++) :: [a] -> [a] -> [a]
(+++) = flip $ foldr (:)

concat1 :: [[a]] -> [a]
concat1 = foldr (++) [] 

reverse1 :: [a] -> [a]
reverse1 = foldl (flip (:)) []

sum1 :: Num a => [a] -> a
sum1 = foldl (+) 0