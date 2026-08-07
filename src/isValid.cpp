#include "../include/isValid.h"
bool isValid(vector<vector<int>> &b, int row, int col, int k)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9 || k < 0 || k > 9)
    {
        return false;
    }
    for (int i = 0; i < 9; i++)
    {
        if (b[row][i] == k)
        {
            return false;
        }
        if (b[i][col] == k)
        {
            return false;
        }
        if (b[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == k)
        {
            return false;
        }
    }
    return true;
}
