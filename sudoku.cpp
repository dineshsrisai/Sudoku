#include <bits/stdc++.h>
using namespace std;

int main()
{
	int board[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}};

	while (true)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n"
			 << "Enter a command : ";
		string s;
		getline(cin, s);

		if (s.substr(0, 3) == "set")
		{
			board[s[4] - 'a'][s[5] - '1'] = s[7] - '0';
		}

		if (s == "exit")
		{
			break;
		}
		cout << s << "\n";
	}
	return 0;
}
