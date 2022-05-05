#ifndef GENERATESUDOKU_H
#define GENERATESUDOKU_H

#define N 9

enum Level {
    EASY=38, MEDUIM=28, HARD=24
};

class GenerateSudoku
{
public:
    static void generateSudoku(int[N][N], int);
    static bool is_safe(int[N][N], int, int, int);
    static bool solve(int[N][N]);
    virtual ~GenerateSudoku();

protected:

private:
    // STEP 1
    static void diagonal_matrices(int[N][N]);
    // STEP 2 __ Solve Sudoku
    // STEP 3
    static void remove_digits(int[N][N], int);
    // HELPING METHODS
    static int random_generator(int, int);
    static void fill_matrix(int[N][N], int, int);
    static bool isValid_matrix(int[N][N], int, int, int);
    static bool isValid_row(int[N][N], int, int);
    static bool isvalid_col(int[N][N], int, int);
    static int getLevel(int);
};

#endif // GENERATESUDOKU_H
