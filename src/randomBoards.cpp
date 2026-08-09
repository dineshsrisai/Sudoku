#include "../include/randomBoards.h"
#include "../include/isValid.h"

bool randomBoards(vector<vector<int>> &b)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (b[i][j] == 0)
            {
                int values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

                for (int k = 8; k > 0; k--)
                {
                    int r = rand() % (k + 1);
                    swap(values[k], values[r]);
                }

                for (int idx = 0; idx < 9; idx++)
                {
                    int val = values[idx];
                    if (isValid(b, i, j, val))
                    {
                        b[i][j] = val;
                        if (randomBoards(b))
                        {
                            return true;
                        }
                        b[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}