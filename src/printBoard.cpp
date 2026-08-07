#include "../include/printBoard.h"
void printBoard(const vector<vector<int>> &b)
{
    
    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6)
        {
            cout << "------+-------+------" << "\n";
        }
        for (int j = 0; j < 9; j++)
        {
            if (j == 3 || j == 6)
            {
                cout << "| ";
            }
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }
}