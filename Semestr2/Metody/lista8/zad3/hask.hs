f::(Int, Int) -> Int
swap::(Int,Int) -> (Int,Int)

g = curry f

f (x,y) = x + 2 *y
swap(x,y) = (y,x)
