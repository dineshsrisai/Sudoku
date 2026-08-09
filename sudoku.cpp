#include <bits/stdc++.h>
#include "./include/isValid.h"
#include "./include/solve.h"
#include "./include/printBoard.h"
#include "./include/saveAndLoad.h"
#include "./include/randomBoards.h"
#include "./include/multiSol.h"

using namespace std;

int numSaves = 0;
string *savedGames = nullptr;
bool run = true;

vector<vector<int>> board = {
	{5, 3, 0, 0, 7, 0, 0, 0, 0},
	{6, 0, 0, 1, 9, 5, 0, 0, 0},
	{0, 9, 8, 0, 0, 0, 0, 6, 0},
	{8, 0, 0, 0, 6, 0, 0, 0, 3},
	{4, 0, 0, 8, 0, 3, 0, 0, 1},
	{7, 0, 0, 0, 2, 0, 0, 0, 6},
	{0, 6, 0, 0, 0, 0, 2, 8, 0},
	{0, 0, 0, 4, 1, 9, 0, 0, 5},
	{0, 0, 0, 0, 8, 0, 0, 7, 9}};

vector<vector<int>> originalBoard = board;

void reset(vector<vector<int>> &b)
{
	b = originalBoard;
}

void signalHandler(int signal)
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
	if (savedGames)
	{
		delete[] savedGames;
		savedGames = nullptr;
	}
}

int main()
{
	srand(time(nullptr));

	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
#ifdef _WIN32
	signal(SIGBREAK, signalHandler);
#endif

	stringstream console;

	ifstream fin("dir.txt");
	if (!fin.fail())
	{
		fin >> numSaves;

		savedGames = new string[numSaves];

		for (int i = 0; i < numSaves; i++)
		{
			fin >> savedGames[i];
		}
	}
	fin.close();
	if (numSaves > 0)
	{
		sort(savedGames, savedGames + numSaves);
	}

	if (!load("autosave.txt", board))
	{
		console << "No autosave found\n";
	}

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
			 << console.str() << "\n";
		console.str("");

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
				console << "Invalid\n";
			}
		}

		if (s.substr(0, 4) == "load")
		{
			if (s.size() > 4)
			{
				string fileName = s.substr(4);
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
				string fileName = s.substr(4);
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
					string *temp = new string[numSaves];
					for (int i = 0; i < numSaves; i++)
					{
						temp[i] = savedGames[i];
					}
					if (savedGames)
					{
						delete[] savedGames;
					}
					savedGames = new string[numSaves + 1];
					for (int i = 0; i < numSaves; i++)
					{
						savedGames[i] = temp[i];
					}
					if (temp)
					{
						delete[] temp;
						temp = nullptr;
					}
					savedGames[numSaves] = fileName;
					numSaves++;
				}
			}
			else
			{
				save("default.txt", board);
			}
		}

		if (s == "list saves")
		{
			console << "Saved Games : " << "\n";
			for (int i = 0; i < numSaves; i++)
			{
				console << savedGames[i] << "\n";
			}
			system("pause");
		}

		if (s.substr(0, 6) == "delete")
		{
			if (s.size() > 6)
			{
				string fileName = s.substr(6);
				while (fileName.size() > 0 && fileName[0] == ' ')
				{
					fileName.erase(0, 1);
				}
				for (int i = 0; i < numSaves; i++)
				{
					if (savedGames[i] == fileName)
					{
						for (int j = i + 1; j < numSaves; j++)
						{
							savedGames[j - 1] = savedGames[j];
							numSaves--;
						}
					}
				}
				remove(fileName.c_str());
			}
		}

		if (s == "solve")
		{
			solve(board);
		}

		if (s.substr(0, 4) == "hint")
		{
			int x = s[5] - 'a', y = s[6] - '1';

			if (x >= 0 && x < 9 && y >= 0 && y < 9)
			{
				vector<vector<int>> temp = board;
				solve(temp);
				console << "Hint : " << char(x + 'a') << char(y + '1') << " " << temp[x][y] << "\n";
			}
			else
			{
				cout << "Invalid\n";
			}
		}

		if (s.substr(0, 3) == "new")
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					board[i][j] = 0;
				}
			}
			randomBoards(board);
			generate(board, 30);

			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					board[i][j] = board[i][j];
				}
			}
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
	}

	if (savedGames)
	{
		delete[] savedGames;
		savedGames = nullptr;
	}

	return 0;
}