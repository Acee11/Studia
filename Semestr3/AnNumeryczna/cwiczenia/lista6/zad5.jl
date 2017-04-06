BF = BigFloat
setprecision(1000)
X = [-2, -1, 0, 1, 2, 3]
Y = [31, 5, 1, 1, 11, 30]
#=
for i = 1:6
    X[i] = BF(X[i])
    Y[i] = BF(Y[i])
end
=#
λ = [1 for i =1:6]

for k = 1:6
    for j = 1:6
        if j == k
            continue
        end
        λ[k] *= X[k] - X[j]
    end
end

for i in 1:6
    @printf "%d / %d\n" Y[i] λ[i]
end
