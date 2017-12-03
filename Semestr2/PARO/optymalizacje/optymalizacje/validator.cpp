#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

typedef std::vector< std::vector<int> > Board;
typedef std::vector< std::vector<int> > Block;

static const int BOARD_SIZE = 9;

bool isValidValue(int x);
Block getBlock(Board b, int index);
bool checkBlock(Block block);
std::vector<int> getColumn(Board b, int index);
bool checkColumn(std::vector<int> col);
std::vector<int> getRow(Board b, int index);
bool checkRow(std::vector<int> row);
bool checkResults(std::vector<bool> blockValidationResults, std::vector<bool> columnValidationResults, std::vector<bool> rowValidationResults);

bool isValidSudoku(Board board)
{
    Block block;
    std::vector<int> column;
    std::vector<int> row;
    bool isValidSize = true;
    bool isValidBlock = true;
    bool isValidRow = true;
    bool isValidColums = true;
    std::vector<bool> blockValidationResults;
    std::vector<bool> columnValidationResults;
    std::vector<bool> rowValidationResults;

    if (board.size() != 9)
    {
        return false;
    }

    for (int i = 0; i < 9; i++)
    {
        auto row = board[i];
        isValidSize = isValidSize && (row.size() == 9);
    }

    if (!isValidSize)
    {
        return false;
    }

    for (unsigned int col = 0; col < BOARD_SIZE; col++)
    {
        for (unsigned int row = 0; row < BOARD_SIZE; row++)
        {
            if (!isValidValue(board[row][col]))
                return false;
        }
    }

    for (unsigned int i = 0; i < 9; i++)
    {
        block = getBlock(board, i);
        blockValidationResults.push_back(checkBlock(block));
    }

    for (unsigned int i = 0; i < 9; i++)
    {
        column = getColumn(board, i);
        columnValidationResults.push_back(checkColumn(column));
    }

    for (int j = 0; j < 9; j++)
    {
        row = getRow(board, j);
        rowValidationResults.push_back(checkRow(row));
    }

    return checkResults(blockValidationResults, columnValidationResults, rowValidationResults);
}

bool isValidValue(int x)
{
    bool isPositive = (x > 0);
    return isPositive && (x < 10);
}

Block getBlock(Board b, int index)
{
    Block blck;

    if (index == 0)
    {
        blck.push_back({b[0][0], b[0][1], b[0][2]});
        blck.push_back({b[1][0], b[1][1], b[1][2]});
        blck.push_back({b[2][0], b[2][1], b[2][2]});
    }
    else if (index == 1)
    {
        blck.push_back({b[0][3], b[0][4], b[0][5]});
        blck.push_back({b[1][3], b[1][4], b[1][5]});
        blck.push_back({b[2][3], b[2][4], b[2][5]});
    }
    else if (index == 2)
    {
        blck.push_back({b[0][6], b[0][7], b[0][8]});
        blck.push_back({b[1][6], b[1][7], b[1][8]});
        blck.push_back({b[2][6], b[2][7], b[2][8]});
    }
    else if (index == 3)
    {
        blck.push_back({b[3][0], b[3][1], b[3][2]});
        blck.push_back({b[4][0], b[4][1], b[4][2]});
        blck.push_back({b[5][0], b[5][1], b[5][2]});
    }
    else if (index == 4)
    {
        blck.push_back({b[3][3], b[3][4], b[3][5]});
        blck.push_back({b[4][3], b[4][4], b[4][5]});
        blck.push_back({b[5][3], b[5][4], b[5][5]});
    }
    else if (index == 5)
    {
        blck.push_back({b[3][6], b[3][7], b[3][8]});
        blck.push_back({b[4][6], b[4][7], b[4][8]});
        blck.push_back({b[5][6], b[5][7], b[5][8]});
    }
    else if (index == 6)
    {
        blck.push_back({b[6][0], b[6][1], b[6][2]});
        blck.push_back({b[7][0], b[7][1], b[7][2]});
        blck.push_back({b[8][0], b[8][1], b[8][2]});
    }
    else if (index == 7)
    {
        blck.push_back({b[6][3], b[6][4], b[6][5]});
        blck.push_back({b[7][3], b[7][4], b[7][5]});
        blck.push_back({b[8][3], b[8][4], b[8][5]});
    }
    else if (index == 8)
    {
        blck.push_back({b[6][6], b[6][7], b[6][8]});
        blck.push_back({b[7][6], b[7][7], b[7][8]});
        blck.push_back({b[8][6], b[8][7], b[8][8]});
    }

    return blck;
}

bool checkBlock(Block block)
{
    std::set<int> values;

    for (auto line : block)
    {
        values.insert(line[0]);
        values.insert(line[1]);
        values.insert(line[2]);
    }

    return values.size() == 9;
}

std::vector<int> getColumn(Board b, int index)
{
    std::vector<int> c;
    for (auto row : b)
    {
        c.push_back(row[index]);
    }

    return c;
}

bool checkColumn(std::vector<int> col)
{
    std::set<int> unique;
    for (auto x : col)
    {
        unique.insert(x);
    }

    return unique.size() == 9;
}

std::vector<int> getRow(Board b, int index)
{
    return b[index];
}

bool checkRow(std::vector<int> row)
{
    auto it = std::unique(row.begin(), row.end());
    row.erase(it, row.end());
    return row.size();

}

bool checkResults(std::vector<bool> blockValidationResults, std::vector<bool> columnValidationResults, std::vector<bool> rowValidationResults)
{
    for (auto x : blockValidationResults)
        if (!x) return false;

    for (auto y : columnValidationResults)
        if (!y) return false;

    for (auto z : rowValidationResults)
        if (!z) return false;

    return true;
}

int main()
{
    Board b1;
    b1.push_back({4, 3, 5, 2, 6, 9, 7, 8, 1});
    b1.push_back({6, 8, 2, 5, 7, 1, 4, 9, 3});
    b1.push_back({1, 9, 7, 8, 3, 4, 5, 6, 2});
    b1.push_back({8, 2, 6, 1, 9, 5, 3, 4, 7});
    b1.push_back({3, 7, 4, 6, 8, 2, 9, 1, 5});
    b1.push_back({9, 5, 1, 7, 4, 3, 6, 2, 8});
    b1.push_back({5, 1, 9, 3, 2, 6, 8, 7, 4});
    b1.push_back({2, 4, 8, 9, 5, 7, 1, 3, 6});
    b1.push_back({7, 6, 3, 4, 1, 8, 2, 5, 9});

    std::cout << "b1 is " << (isValidSudoku(b1) ? "" : "not ") << "valid\n";

    Board b2;
    b2.push_back({4, 3, 5, 2, 6, 9, 7, 8, 1});
    b2.push_back({6, 8, 2, 5, 7, 1, 4, 9, 3});
    b2.push_back({1, 9, 7, 8, 3, 4, 5, 6, 2});
    b2.push_back({8, 2, 6, 1, 9, 5, 3, 4, 7});
    b2.push_back({3, 7, 4, 6, 8, 2, 9, 1, 5});
    b2.push_back({9, 5, 1, 7, 4, 3, 6, 2, 8});
    b2.push_back({5, 1, 9, 3, 2, 6, 8, 7, 4});
    b2.push_back({2, 4, 8, 9, 5, 7, 1, 3, 6});
    b2.push_back({9, 6, 3, 4, 1, 8, 2, 5, 9});

    std::cout << "b2 is " << (isValidSudoku(b2) ? "" : "not ") << "valid\n";
}
