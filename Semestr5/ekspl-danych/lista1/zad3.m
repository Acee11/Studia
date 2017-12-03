d = 100;
N = 1000;
x = rand(d,1);
y = rand(d,1);
w = rand(d,1);
% dlugosc
sqrt(x'*x)
% srednia wazona
sum(x.*w)/d
% odleglosc euklidesowa
tmp = x-y
sqrt(tmp'*tmp)
% iloczyn skalarny
x'*x

X = rand(d, N);
% dlugosci
sqrt(sum(X.*X))
% srednie wazone
sum(bsxfun(@times, X, w))./d
% odleglosci
sqrt(sum(bsxfun(@minus, X, y)))
% iloczyny skalarne
sum(bsxfun(@minus, X, y))
