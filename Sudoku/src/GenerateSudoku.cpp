#include "GenerateSudoku.h"
#include <bits/stdc++.h>

#define STEP 3

void GenerateSudoku::generateSudoku(int board[N][N], int level)
{
    // TO (rand()) EACH TIME GENERATE NEW COMBINATION OF NUMBERS :)
    srand(time(0));
    // FILL THE DIAGONAL MATRICES
    diagonal_matrices(board);
    // FILL THE REST OF THE BOARD
    solve(board);
    // REMOVE DIGITS ACCORDING TO THE LEVEL USER NEED
    int numOfRemovingCells = N * N - getLevel(level);
    remove_digits(board, numOfRemovingCells);
}

void GenerateSudoku::diagonal_matrices(int board[N][N])
{
    for (int i = 0; i < N; i += STEP)
    {
        fill_matrix(board, i, i); // board, row, column
    }
}

void GenerateSudoku::fill_matrix(int board[N][N], int row, int col)
{
    int num;
    for (int i = row; i < row + STEP; i++)
    {
        for (int j = col; j < col + STEP; j++)
        {
            do
            {
                num = random_generator(1, N);
            }
            while (!isValid_matrix(board, row, col, num));
            board[i][j] = num;
        }
    }
}

int GenerateSudoku::random_generator(int num1, int num2)
{
    return (num1 + rand() % num2);
}

bool GenerateSudoku::isValid_matrix(int board[N][N], int row, int col, int num)
{
    for (int i = row; i < STEP + row; i++)
        for (int j = col; j < STEP + col; j++)
            if (board[i][j] == num)
                return false;
    return true;
}

bool GenerateSudoku::isValid_row(int board[N][N], int row, int num)
{
    for (int i = 0; i < N; i++)
        if (board[row][i] == num)
            return false;
    return true;
}

bool GenerateSudoku::isvalid_col(int board[N][N], int col, int num)
{
    for (int i = 0; i < N; i++)
        if(board[i][col] == num)
            return false;
    return true;
}

bool GenerateSudoku::is_safe(int board[N][N], int row, int col, int num)
{
    return isValid_row(board, row, num) &&
           isvalid_col(board, col, num) &&
           isValid_matrix(board, row - row % STEP, col - col % STEP, num);
}

bool GenerateSudoku::solve(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(board[i][j] == 0) {
                // WATCH OUT __ BACKTRACKING
                for (int k = 1; k <= N; k++) {
                    if (GenerateSudoku::is_safe(board, i, j, k)) {
                        board[i][j] = k;
                        if (solve(board)) {
                            return true;
                        }
                        board[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}



int GenerateSudoku::getLevel(int level)
{
    int res;
    switch (level)
    {
    case 0: // ESAY
        res = random_generator(Level::EASY, STEP);
        break;
    case 1: // MEDUIM
        res = random_generator(Level::MEDUIM, STEP);
        break;
    case 2: // HARD
    default:
        res = random_generator(Level::HARD, STEP);
    }
    return res;
}

void GenerateSudoku::remove_digits(int board[N][N], int numOfRemove)
{
    while (numOfRemove != 1)
    {
        int val = random_generator(0, N * N);
        int i = (val / N);
        int j = val % 9;
        if (j != 0) j = j - 1;

        if (board[i][j] != 0)
        {
            numOfRemove--;
            board[i][j] = 0;
        }
    }
}

GenerateSudoku::~GenerateSudoku()
{
    // CLEAN
}
