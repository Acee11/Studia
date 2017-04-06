function simpson(n, f, a, b)
    assert(n%2 == 0)
    h = (b-a)/n
    X = linspace(a, b, n+1)
    S = 0
    for k = 1:(n+1)
        t = f(X[k])
        t *= isodd(k) ? 2 : 4
        if(k == 1 || k == n + 1)
            t /= 2
        end
        S += t
    end
    return S * h/3
end

function T(n, f, a, b)
    h = (b-a)/n
    X = map(f, linspace(a, b, n+1))
    X[1] /= 2
    X[n+1] /= 2
    return sum(X) * h 
end

@printf "%.3e\n" abs(simpson(16, sin, zero(Float64), Float64(pi)) - 2.0)
#@printf "%.3e\n" abs(T(4*8, sin, zero(Float64), Float64(pi)/2) - one(Float64))
@printf "%.3e\n" abs(T(288, sin, zero(Float64), Float64(pi)) - 2.0)