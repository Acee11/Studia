import numpy as np
import fractions as fr
a = np.array([[1, 2, 2], 
			  [1, 4, 8],
			  [1, 8, 24]])
b = np.array([2, 10, 34])
x = np.linalg.solve(a, b)

print(x)
