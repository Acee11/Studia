using Polynomials

n = 4
p = Poly([-2,1])


for i = 1:n
    p *= p
    @printf "Iter: %d\n" i 
    println(p[2])
    println()
    p -= 2
end

ak = 4
for i = 1:n
    @printf "Iter: %d\n" i 
    println((ak*ak - ak)/12)
    println()
    ak *= 4
end


