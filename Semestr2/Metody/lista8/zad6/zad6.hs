module Practice where
import Prelude hiding (Enum, fromEnum, toEnum)

class Enum a where
	fromEnum :: a -> Int
	toEnum :: Int -> a

data Number = Zero
data Color = Yellow

{-
instance Enum (a,b) where
	fromEnum Zero = 0
	toEnum 0 = Zero
-}
instance Enum Color where
	fromEnum Yellow = 1
	toEnum 1 = Yellow  

instance Enum Number where
	fromEnum Zero = 1
	toEnum 1 = Zero  
	


instance  (Enum a, Enum b) => Enum (a,b) where
	fromEnum (a, b) = fromEnum a + fromEnum b
	toEnum i = (toEnum i, toEnum i)






