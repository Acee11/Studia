BF = BigFloat
setprecision(1000)


function factorial(n)
    if(n <= 1)
        return 1
    end
    s = 1
    for i=2:n
        s *= i
    end
    return s
end

f(n) = BF(e)/((BF(2)^n) * factorial(n+1))

i = 1
while(f(i) > BF(10e-5))
    i += 1
end
@printf "%f   %d\n" f(i-1) i