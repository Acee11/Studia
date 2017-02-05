nat :: [(Integer, Integer)]
nat = [(x,m-x) | m <- [0..],x <- [0..m]] 