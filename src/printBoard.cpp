#include "../include/printBoard.h"
void printBoard(const vector<vector<int>> &b)
{
    cout << "Use Cmd 'menu' \n";
    cout << "\n";
    cout << "   1 2 3   4 5 6   7 8 9 " << "\n";
    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6)
        {
            cout << "   ------+-------+------" << "\n";
        }
        cout << char('A' + i) << "  ";
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