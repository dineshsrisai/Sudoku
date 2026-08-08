#include "../include/saveAndLoad.h";

bool save(string fileName, const vector<vector<int>> &b)
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

bool load(string fileName, vector<vector<int>> &b)
{
    ifstream fin;

    fin.open(fileName);
    if (fin.fail())
    {
        fin.close();
        return false;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fin >> b[i][j];
        }
    }
    fin.close();
    return true;
}