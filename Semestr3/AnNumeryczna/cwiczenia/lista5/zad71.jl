setprecision(128)

using Polynomials

function solveQuadratic(a, b, c)

  delta = b*b - 4 * a * c

  if delta < 0
    x1 = Complex(-b/(2*a), -sqrt(-delta)/(2*a))
    x2 = Complex(-b/(2*a), +sqrt(-delta)/(2*a))
    return [x1, x2]

  else
    x1 = Complex((-b - sqrt(delta))/(2*a))
    x2 = Complex((-b + sqrt(delta))/(2*a))
    return [x1, x2]
  end
end

function bairstow(a, u, v, iter)
    n = length(a)-1
    a = map(x->parse(BigFloat, string(x)), a)
    u = parse(BigFloat, string(u))
    v = parse(BigFloat, string(u))
    res = Array(Complex{BigFloat}, 0)
    res1 = Array(Array{BigFloat}, 0)
    J = BigFloat(0)


    while(n > 0)
        if n == 1
          append!(res, [Complex(-a[1]/a[2])]) # x = -b/a
          append!(res1, [[0,a[2],a[1]]])
          break
        end

        if n == 2
          append!(res, solveQuadratic(a[3], a[2], a[1]))
          append!(res1, [[a[3], a[2], a[1]]])
          break
        end

        b  = [zero(BigFloat) for i in 1:(n+3)]
        c  = [zero(BigFloat) for i in 1:(n+3)]
        b[n+1] = a[n+1]
        c[n] = a[n+1]

        for j in 1:iter
            b[n] = a[n] + u * b[n+1]

            k = n-2

            while k >= 0
                b[k+1] = a[k+1] + u * b[k+2] + v * b[k+3]
                c[k+1] = b[k+2] + u * c[k+2] + v * c[k+3]
                k -= 1
            end
            J = c[1] * c[3] - c[2] * c[2]
            u = u + (c[2]*b[2] - c[3] * b[1] ) / J
            v = v + (c[2]*b[1] - c[1] * b[2]) / J
        end
        append!(res, solveQuadratic(1, -u, -v))
        append!(res1, [[1,u,v]])
        a = copy(b[3:end])
        n -= 2
    end
    return (res, res1)
end

res = bairstow([1,2,3,4,5], BigFloat(0.1), BigFloat(0.1), 10)

for i in res[2]
    @printf "%1.3g x^2 + %1.3g x + %1.3g\n\n" i[3] i[2] i[1]
end

for i in res[1]
    @printf "x0 = %.16f + %.16fi\n\n" real(i) imag(i)
end
println("----------------------------------")
pol = Poly([1,2,3,4,5])
for i in roots(pol)
    @printf "x1 = %.16f + %.16fi\n\n" real(i) imag(i)
end

#=
-0.418 x^2 + -1.08 x + 1

2.39 x^2 + -1.38 x + 5

x0 = -0.5378322749029900 + -0.3582846863451280i

x0 = -0.5378322749029900 + 0.3582846863451280i

x0 = 0.1378322749029900 + -0.6781543891053364i

x0 = 0.1378322749029900 + 0.6781543891053364i

----------------------------------
x1 = 0.1378322749029903 + 0.6781543891053368i

x1 = 0.1378322749029903 + -0.6781543891053368i

x1 = -0.5378322749029900 + 0.3582846863451283i

x1 = -0.5378322749029900 + -0.3582846863451283i
=#