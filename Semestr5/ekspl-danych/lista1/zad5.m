d = 100;
N = 10000;
M = 1000;

X = rand(d, N);
Y = rand(d, M);

tic
res = knn(X, Y);
toc

