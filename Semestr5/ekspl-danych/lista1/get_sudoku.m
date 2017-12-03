function sudoku = get_sudoku()
rounds = 100;
sudoku = [[4 3 5 2 6 9 7 8 1];
     [6 8 2 5 7 1 4 9 3];
     [1 9 7 8 3 4 5 6 2];
     [8 2 6 1 9 5 3 4 7];
     [3 7 4 6 8 2 9 1 5];
     [9 5 1 7 4 3 6 2 8];
     [5 1 9 3 2 6 8 7 4];
     [2 4 8 9 5 7 1 3 6];
     [7 6 3 4 1 8 2 5 9]];
rswap = [1; 4; 7];   

for i = 1:rounds
    rblock = rswap(randi(3));
    ch1 = randi([rblock, rblock+2]);
    ch2 = randi([rblock, rblock+2]);
    sudoku(:, [ch1, ch2]) = sudoku(:, [ch2, ch1]);

    rblock = rswap(randi(3));
    ch1 = randi([rblock, rblock+2]);
    ch2 = randi([rblock, rblock+2]);
    sudoku([ch1, ch2], :) = sudoku([ch2, ch1], :);

    if randi(2) == 1
        sudoku = sudoku';
    end
end

end


