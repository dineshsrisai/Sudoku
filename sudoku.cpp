#include <bits/stdc++.h>
#include "./include/isValid.h"
#include "./include/solve.h"
#include "./include/printBoard.h"
#include "./include/saveAndLoad.h"
using namespace std;

int main()
{
	vector<vector<int>> board(9, vector<int>(9, 0));

	load("autosave.txt", board);

	while (true)
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

		if (s == "exit")
		{
			save("autosave.txt", board);
			break;
		}
		cout << s << "\n";
	}
	return 0;
}