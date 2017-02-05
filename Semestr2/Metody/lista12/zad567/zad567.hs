import Control.Applicative 
import Control.Monad       

data Cyclist a = Elem (Cyclist a) a (Cyclist a)

f1 :: [a] -> Cyclist a -> Cyclist a -> Cyclist a
f1 [x] a b = (Elem a x b)
f1 (x:xs) a b = res where
	res = Elem a x (f1 xs res b)

f2 :: [a] -> Cyclist a -> Cyclist a -> Cyclist a
f2 [x] a b = Elem a x b
f2 (x:xs) a b = res where
	res = Elem (f2 xs a res) x b   


fromList :: [a] -> Cyclist a
fromList [x] = Elem (fromList [x]) x (fromList [x])
fromList (x:xs) = res where
	res = Elem prev x next
	prev = f2 (reverse xs) res res
	next = f1 xs res res

forward :: Cyclist a -> Cyclist a
forward (Elem _ _ x) = x

backward :: Cyclist a -> Cyclist a
backward (Elem x _ _) = x
label :: Cyclist a -> a
label (Elem _ x _) = x


enumInts :: Cyclist Integer
enumInts = fromList [0..]


newtype Cyc a b =
	Cyc (Cyclist a -> (b, Cyclist a))
     
instance Functor (Cyc a) where
    fmap = liftM

instance Applicative (Cyc a) where
    pure x = Cyc (\state -> (x, state))
    (<*>) = ap

instance Monad (Cyc a) where
	return = pure
	(Cyc comp) >>= f = 
			Cyc (\state -> 
			let (x, state1) = comp state ; Cyc comp1 = f x                                  
			in comp1 state1) 

runCyc :: Cyclist a -> Cyc a b -> b
runCyc a (Cyc f) = fst $ f a

fwd :: Cyc a ()
fwd = Cyc (\state -> ((), forward state))

bkw :: Cyc a ()
bkw = Cyc (\state -> ((), backward state))

lbl :: Cyc a a
lbl = Cyc (\state -> (label state, state))

example :: Integer
example = runCyc enumInts (do
	fwd
	fwd
	fwd
	fwd
	x <- lbl
	bkw
	bkw
	y <- lbl
	fwd
	z <- lbl
	return (x + y + z))

