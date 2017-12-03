function res = get_dists(X, Y)
res = sqrt(squeeze(sum(bsxfun(@minus, X', reshape(Y, 1, size(Y, 1), size(Y, 2))).^2, 2)));
end
