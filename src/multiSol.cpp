#include "../include/isValid.h"
#include "../include/multiSol.h"

bool multiSol(vector<vector<int>> &b, int &numSol)
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
                        if (multiSol(b, numSol))
                        {
                            b[i][j] = 0;
                            return true;
                        }
                        b[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    numSol++;
    return numSol >= 2;
}
