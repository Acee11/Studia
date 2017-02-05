setprecision(1000)
Fl = BigFloat

X = [0; 1; 2; 4; 6]
F = [1; 9; 23; 93; 259]
X = map(Fl, X)
F = map(Fl, F)

A = Array{Fl}(4,4)
for i = 1:4, j = 1:4
    A[i,j] = sum([X[k]^(i+j-2) for k = 1:5])
end

B = Array{Fl}(4,5)
for i = 1:4, j = 1:5
    B[i,j] = X[j]^(i-1)
end
BF = B*F
for i in \(A,BF)
    @printf "%.3e\n" i
end

w(x) = x^3 + 7x + 1

print(w(6)) 



