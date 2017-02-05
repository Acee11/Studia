#############################################
#                                           #
#           Autor: Wojciech Balik           #
#                                           #
#############################################

include("program.jl")
function getRandPoly(n, deg)
    T = Array{Array{Float64}}(n)
    
    for i  = 1:n
        T[i] = map(x -> x * (rand(Int64)%500), rand(deg+1))
    end
    return T
end

function polyToFile(P, fname)
    out = open("test/"*fname, "w")
    for poly in P
        for i in poly
            write(out, string(i), " ")
        end
        write(out,"\n")
    end
    close(out)
end

function fileToPoly(fname, T)
    input = open("test/"*fname, "r")
    P = map(chomp, readlines(input))
    res = Array{Array{T}}(0)
    for i in P
        push!(res, map(x -> parse(T, x), split(chop(i), " ")))
    end
    close(input)
    return res
end

function test(n, polys, T, R, k)
    X = Array(linspace(-T(10), T(10), n))
    LagrError = 0
    NewtError = 0
    BarError = 0
    LagrNewtError = 0
    Bar1Error = 0
    for pol in polys
        Y = map(pol, X)
        pol = Poly([BigFloat(pol[i]) for i = 0:9])
        SLagr = 0
        SNewt = 0
        SBar = 0
        SLagrNewt = 0
        SBar1 = 0
        Lagr = LagrangePoly(X,Y)
        Newt = NewtonPoly(X,Y)
        Bar = BarPoly(X,Y)
        LagrNewt = lagrToNewton(Lagr)
        m = sum(X)/(n+1)
        X1 = sort(X, lt = (x,y) -> abs(x-m) < abs(y-m) ? true : false)
        Y1 = map(pol, X1)
        Bar1 = BarPoly(X1, Y1)
        for i in linspace(-T(R), T(R), k)
            #println(typeof(pol(i)), typeof(Lagr(i)))
            p = T(pol(i))
            #@printf "%f\n%f\n%f\n%f\n\n\n" p abs((Lagr(i) - p)/p) abs((Newt(i) - p)/p) abs((Bar(i) - p)/p)
            SLagr += abs((Lagr(i) - p)/p)
            SNewt += abs((Newt(i) - p)/p)
            SBar += abs((Bar(i) - p)/p)
            SLagrNewt += abs((LagrNewt(i) - p)/p)
            SBar1 += abs((Bar1(i) - p)/p)
        end
        LagrError += SLagr/k
        NewtError += SNewt/k
        BarError += SBar/k
        LagrNewtError += SLagrNewt/k
        Bar1Error += SBar1/k
        #@printf "%f\n\n" SLagr/k
    end
    l = length(polys)
    return (LagrError/l, NewtError/l, BarError/l, Bar1Error/l, LagrNewtError/l)
end

function chebyshev(n)
    return [cospi((2*i-1)/(2*n)) for i = 1:n]
end

