#include <bits/stdc++.h>
#include "./include/isValid.h"
#include "./include/solve.h"
#include "./include/printBoard.h"
#include "./include/saveAndLoad.h"
#include "./include/randomBoards.h"
#include "./include/multiSol.h"
using namespace std;

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

string trimLeadingSpaces(string s)
{
	while (!s.empty() && s[0] == ' ')
	{
		s.erase(0, 1);
	}
	return s;
}

void signalHandler(int signal)
{
	save("autosave.txt", board);
	exit(0);
}

int main()
{
	srand((unsigned int)time(nullptr));
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
#ifdef _WIN32
	signal(SIGBREAK, signalHandler);
#endif

	stringstream console;

	if (!load("autosave.txt", board))
	{
		console << "No autosave found\n";
	}
	originalBoard = board;

	while (run)
	{
		printBoard(board);
		cout << "\n";
		cout << console.str() << "\n";
		console.str("");
		cout << "\nEnter a command : ";
		string s;
		getline(cin, s);
		if (s == "menu")
		{
			console << "Commands:\n";
			console << "  set <row><col> <val>  - e.g. set a1 5\n";
			console << "  hint <row><col>       - e.g. hint a1\n";
			console << "  solve                 - auto-solve the board\n";
			console << "  new                   - generate a new puzzle\n";
			console << "  clear                 - reset to original puzzle\n";
			console << "  save <name>           - save current board\n";
			console << "  load <name>           - load a saved board\n";
			console << "  exit                  - save and quit\n";
		}
		if (s.substr(0, 3) == "set")
		{
			if (s.size() < 8)
			{
				console << "Invalid\n";
			}
			else
			{
				int row = s[4] - 'a', col = s[5] - '1', val = s[7] - '0';
				if (row >= 0 && row < 9 && col >= 0 && col < 9 && val >= 1 && val <= 9 && isValid(board, row, col, val))
				{
					board[row][col] = val;
				}
				else
				{
					console << "Invalid\n";
				}
			}
		}

		else if (s.substr(0, 4) == "load")
		{
			string fileName = s.size() > 4 ? trimLeadingSpaces(s.substr(4)) : "default.txt";
			if (!load(fileName, board))
			{
				console << "Could not load " << fileName << "\n";
			}
			else
			{
				originalBoard = board;
			}
		}

		else if (s.substr(0, 4) == "save")
		{
			string fileName = s.size() > 4 ? trimLeadingSpaces(s.substr(4)) : "default.txt";
			if (save(fileName, board))
			{
				console << "Saved to " << fileName << "\n";
			}
			else
			{
				console << "Could not save to " << fileName << "\n";
			}
		}

		else if (s == "solve")
		{
			solve(board);
		}

		else if (s.substr(0, 4) == "hint")
		{
			if (s.size() < 7)
			{
				console << "Invalid\n";
			}
			else
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
					console << "Invalid\n";
				}
			}
		}

		else if (s == "clear")
		{
			reset(board);
		}

		else if (s.substr(0, 3) == "new")
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
			originalBoard = board;
		}

		else if (s == "exit")
		{
			save("autosave.txt", board);
			run = false;
		}

		else if (!s.empty())
		{
			console << "Unknown command\n";
		}
	}

	return 0;
}
