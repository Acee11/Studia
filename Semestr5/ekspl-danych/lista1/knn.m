function res = knn(X, Y, k)
[D, I] = sort(get_dists(X, Y), 2);
res = I(:, 1:k);
end
