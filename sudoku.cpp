#include <bits/stdc++.h>
#include "./include/isValid.h"
#include "./include/solve.h"
#include "./include/printBoard.h"
#include "./include/saveAndLoad.h"
using namespace std;

int main()
{

	int numSaves = 0;
	string savedGames[1000];

	ifstream fin("dir.txt");
	if (!fin.fail())
	{
		fin >> numSaves;
		for (int i = 0; i < numSaves; i++)
		{
			fin >> savedGames[i];
		}
	}
	fin.close();
	sort(savedGames, savedGames + numSaves);

	vector<vector<int>> board(9, vector<int>(9, 0));

	load("autosave.txt", board);
	bool run = true;
	while (run)
	{
		// preprocessor directives eg : headerfiles
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif

		printBoard(board);
		cout << "\n"
			 << "Enter a command : ";
		string s;
		getline(cin, s);
		if (s.substr(0, 3) == "set")
		{
			int row = s[4] - 'a', col = s[5] - '1';
			int val = s[7] - '0';
			if (row >= 0 && row < 9 && col >= 0 && col < 9)
			{
				if (isValid(board, row, col, val))
				{
					board[row][col] = val;
				}
			}
			else
			{
				cout << "Invalid\n";
			}
		}

		if (s.substr(0, 4) == "load")
		{
			if (s.size() > 4)
			{
				string fileName = s.substr(0, 4);
				while (fileName.size() > 4 && fileName[0] == ' ')
				{
					fileName.erase(0, 1);
				}
				load(fileName, board);
			}
			else
			{
				load("default.txt", board);
			}
		}

		if (s.substr(0, 4) == "save")
		{
			if (s.size() > 4)
			{
				string fileName = s.substr(0, 4);
				while (fileName.size() > 4 && fileName[0] == ' ')
				{
					fileName.erase(0, 1);
				}
				save(fileName, board);

				bool exists = false;
				for (int i = 0; i < numSaves; i++)
				{
					if (savedGames[i] == fileName)
					{
						exists = true;
					}
				}
				if (!exists)
				{
					savedGames[numSaves] = fileName;
					numSaves++;
				}
			}
			else
			{
				save("default.txt", board);
			}
		}

		if (s == "listSaves")
		{
			cout << "Saved Games : " << "\n";
			for (int i = 0; i < numSaves; i++)
			{
				cout << savedGames[i] << "\n";
			}
			system("pause");
		}

		if (s == "exit")
		{
			save("autosave.txt", board);
			run = false;
			ofstream fout("dir.txt");
			fout << numSaves << "\n";
			for (int i = 0; i < numSaves; i++)
			{
				fout << savedGames[i] << "\n";
			}
			fout.close();
		}
		cout << s << "\n";
	}
	return 0;
}