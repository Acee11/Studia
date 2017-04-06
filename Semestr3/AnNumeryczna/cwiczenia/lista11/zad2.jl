BF = BigFloat
using Polynomials

f(x) = BF(1)/(BF(1)+x*x)

g(k,n) = vcat(0:(k-1), (k+1):n)

function newtonCotesCoeff(n, a, b)
    T = typeof(a)
    h = (b-a)/T(n)
    return [h * ((-one(T))^(n-k)) * T(1/(factorial(k) * factorial(n-k))) * T(polyint(poly(g(k,n)))(n)) for k = 0:n]
end

function Q(f, n)
    X = linspace(-BF(4), BF(4), n+1)
    A = newtonCotesCoeff(n, -BF(4), BF(4))
    return sum([f(X[k]) * A[k] for k = 1:(n+1)])
end

function bool(f)
    Y = [f(x) for x in linspace(-BF(4), BF(4), 5)]
    return (4/45) * (7*Y[1] + 32*Y[2] + 12*Y[3] + 32*Y[4] + 7*Y[5])
end


realVal = 4*atan(4)

println(realVal)
for i in [2,4,6,8,10]
    @printf "%d   |   %.3f\n" i abs(Q(f,i) - realVal)
end



