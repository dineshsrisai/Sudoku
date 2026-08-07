#include "../include/save.h";
bool save(string fileName, vector<vector<int>> &b)
{
    ofstream fout;
    fout.open(fileName);

    if (fout.fail())
    {
        fout.close();
        return false;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fout << b[i][j] << " ";
        }
        fout << "\n";
    }

    fout.close();
    return true;
}