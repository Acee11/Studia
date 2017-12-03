a = [1:100]
b = [1:2:100]
c = [-pi:0.01*pi:pi]
d = [[-pi:0.01*pi:-0.01*pi], [0.01*pi: 0.01*pi:pi]]
e = max(0,sin([1:100]))
A = reshape([1:100], 10, 10)'
B = diag([1:100], 0) + diag([99:-1:1], -1) + diag([99:-1:1], 1)
C = triu(ones(10, 10))
D = [cumsum(1:100); factorial(1:100)]
E = bsxfun(@mod, [1:100], [1:100]')
E(E ~= 0) = [1]
E = 1-E
