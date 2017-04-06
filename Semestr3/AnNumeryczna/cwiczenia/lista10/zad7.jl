include("test_functions.jl")

f(x) = 1/(1+25*x^2)

Fl = BigFloat
setprecision(1024)
#a
X = map(Fl, Array(linspace(-1,1,10)))
Y = map(f, X)
W = BarPoly(X, Y)





