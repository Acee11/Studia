#############################################
#                                           #
#           Autor: Wojciech Balik           #
#                                           #
#############################################

using Polynomials

setprecision(128)

function getLagrCoeff(X::Array, Y::Array)
    T = typeof(X[1])
    @assert length(X) == length(Y)
    n = length(X)
    cf = Array{T}(n)
    for k = 1:n
        s = 1
        for j = 1:n
            if j==k
                continue
            end
            s *= X[k] - X[j]
        end
        cf[k] = Y[k]/s
    end 
    return cf
end

type LagrangePoly
    coeff::Array
    X::Array
    Y::Array
    LagrangePoly(X1, Y1) = new(getLagrCoeff(X1,Y1), X1, Y1)  
end

function (p::LagrangePoly)(x)
    s = 0
    n = length(p.X)
    for i = 1:n
        m = 1
        for j = 1:n
            if i == j
                continue
            end
            m *= x - p.X[j]
        end
        s += m*p.coeff[i]
    end
    return s
end

function getNewtonCoeff(X::Array, Y::Array)
    @assert length(X) == length(Y)
    n = length(X)
    M = copy(Y)
    for i = 2:n
        j = n
        while(j >= i)
            M[j] = (M[j] - M[j-1])/(X[j] - X[j - i + 1])
            j -= 1
        end
    end
    return M
end

type NewtonPoly
    coeff::Array
    X::Array
    Y::Array
    NewtonPoly(X, Y) = new(getNewtonCoeff(X, Y), X, Y)
    NewtonPoly(C, X, Y) = new(C, X, Y)
end

function (p::NewtonPoly)(x)
    n = length(p.X)
    s = p.coeff[n]
    i = n-1
    while(i >= 1)
        s = s*(x - p.X[i]) + p.coeff[i]
        i -= 1
    end
    return s
end

function getBarCoeff1(X) #algorytm naiwny
    T = typeof(X[1])
    n = length(X)
    W = Array{T}(n)
    for i = 1:n
        s = one(T)
        for j in 1:n
            if i == j
                continue
            end
            s *= 1/(X[i] - X[j])
        end
        W[i] = s
    end
    return W
end

function getBarCoeff(X) #algorytm Wernera
    T = typeof(X[1])
    n = length(X)
    a = Array{T}(n)
    a[1] = 1
    for k = 2:n
        a[k] = 0
    end

    for i = 2:n
        for k = 1:(i-1)
            a[k] = a[k]/(X[k] - X[i])
            a[i] = a[i] - a[k]
        end
    end


    return [a[i] for i in 1:n]
end

type BarPoly
    coeff::Array
    X::Array
    Y::Array
    BarPoly(X,Y) = new(getBarCoeff(X), X, Y)
end

function (p::BarPoly)(x)
    T = typeof(p.X[1])
    n = length(p.X)
    for i = 1:n
        if abs(x - p.X[i]) < eps(T)
            return p.Y[i]
        end
    end
    s1 = 0
    s2 = 0
    for i = 1:n
        t = p.coeff[i] / (x - p.X[i])
        s1 += t * p.Y[i]
        s2 += t
    end
    return s1/s2
end


function lagrToNewton(p::LagrangePoly)
    T = typeof(p.X[1])
    n = length(p.coeff)
    M = Array{T}(n)
    X1 = p.X

    for i = 1:n
        M[i] = p.coeff[i]
    end
    for k = 1:n
        M[n-k+1] = sum([M[i] for i in 1:(n-k+1)])
        i = n-k
        while(i >= 1)
            M[i] = (X1[i] - X1[n-k+1])*M[i]
            i -= 1
        end
    end
    return NewtonPoly(M, copy(p.X), copy(p.Y))
end

