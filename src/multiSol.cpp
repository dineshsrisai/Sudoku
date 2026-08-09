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
                            return true;
                        }
                    }
                }
                b[i][j] = 0;
                return false;
            }
        }
    }
    numSol++;
    return numSol >= 2;
}

bool generate(vector<vector<int>> &b, int numEntries)
{
    int xList[81], yList[81];
    int nonNumEmpties = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (b[i][j] != 0)
            {
                xList[nonNumEmpties] = i;
                yList[nonNumEmpties] = j;
                nonNumEmpties++;
            }
        }
    }

    if (nonNumEmpties <= numEntries)
    {
        return true;
    }

    while (nonNumEmpties)
    {
        int idx = rand() % nonNumEmpties;
        int x = xList[idx], y = yList[idx];
        nonNumEmpties--;

        for (int i = idx; i < nonNumEmpties; i++)
        {
            xList[i] = xList[i + 1];
            yList[i] = yList[i + 1];
        }

        int val = b[x][y];
        b[x][y] = 0;

        int numSol = 0;
        if (!multiSol(b, numSol) && generate(b, numEntries))
        {
            return true;
        }

        b[x][y] = val;
    }
    return false;
}