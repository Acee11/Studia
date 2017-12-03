d = 100;
N = 1000;
M = 1000;

X = rand(d, N);
Y = rand(d, M);

tic
edist = squeeze(sqrt(sum(bsxfun(@minus, X', reshape(Y, 1, size(Y, 1), size(Y, 2))).^2, 2)));
toc
