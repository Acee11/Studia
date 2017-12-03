n = 1000000
choice = randi(3, 1, n);
reward = randi(3, 1, n);
sum(choice ~= reward)/n