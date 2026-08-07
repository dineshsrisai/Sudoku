#include "../include/solve.h"
#include "../include/isValid.h"

bool solve(vector<vector<int>> &b)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (b[i][j] == 0)
            {
                for (int k = 1; k <= 9; k++)
                {
                    if (isValid(b, i, j, k))
                    {
                        b[i][j] = k;
                        if (solve(b))
                        {
                            return true;
                        }
                        else
                        {
                            b[i][j] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}