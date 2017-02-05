roots :: (Double, Double, Double) -> [Double]
roots (a,b,c) 
  	| delta > 0		= [(-b - sqrt delta)/(2*a), (-b + sqrt delta)/(2*a)]
  	| delta == 0	= [(-b  / (2*a))]  
  	| otherwise     = []	
  	where delta = (b*b - 4 * a * c)

data Roots = No
		| One Double
		| Two (Double, Double)
		deriving Show
roots1 :: (Double, Double, Double) -> Roots
roots1 (a,b,c)
	| delta > 0 = Two ((-b - sqrt delta)/(2*a), (-b + sqrt delta)/(2*a))
	| delta == 0 = One (-b  / (2*a))
	| otherwise = No
	where delta = (b*b - 4 * a * c)