import Data.List
import Data.Char

f :: Integer -> Maybe(Char, Integer)
f x 
  | x == 0 = Nothing
  | otherwise = Just (intToDigit( fromEnum(x) `mod` 10 ),x `div` 10 )

integerToString :: Integer -> String
integerToString x
  | x == 0 = "0" 
  | x > 0 = reverse(unfoldr f x)
  | otherwise = "-" ++ reverse(unfoldr f (-x))

