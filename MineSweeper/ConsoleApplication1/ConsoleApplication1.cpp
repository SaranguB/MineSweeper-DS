#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
using namespace std;

class MineSweeper
{
private:
	vector <vector<int>> board;

public:

	void InitializeBoard(int n)
	{
		board.resize(n, vector<int>(n, 0));
	}

	void DisplayMatrix(int n)
	{

		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				cout << " | ";

				if (board[i][j] == -1)
				{
					cout << " * ";

				}
				else if(board[i][j] != 0)
				{
					cout << " " << board[i][j] << " ";
				}
				else
				{
					cout << " . ";
				}
			}
			cout << endl << endl;
		}
	}


	void PlaceMine(int n, int mineCount, int chooseX, int chooseY)
	{
		srand(time(0));
		int placedMine = 0;

		while (placedMine < mineCount)
		{
			int x = rand() % n;
			int y = rand() % n;

			if (board[x][y] == 0 && (x != chooseX || y != chooseY))
			{
				board[x][y] = -1;
				placedMine++;
			}

		}

	}

	void DisplayMine(int n)
	{
		for (int i = 0;i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{

				cout << (board[i][j] == 1 ? "* " : ". ");
			}
			cout << endl;
		}
	}

	void PlaceNumbers(int n, int chooseX, int chooseY)
	{
		int mineCount = 0;

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (dx == 0 && dy == 0)
					continue;


				int newX = chooseX + dx;
				int newY = chooseY + dy;

				if (newX >= 0 && newX < n && newY >= 0 && newY < n)
				{
					if (board[newX][newY] == -1)
					{
						mineCount++;
					}
				}

			}
		}

		board[chooseX][chooseY] = mineCount;


		for (int i = 0;i < n;i++)
		{
			for (int j = 0; j < n;j++)
			{

				if (i == chooseX && j == chooseY)
					continue;

				if (board[i][j] == -1)
					continue;


				 mineCount = 0;

				for (int dx = -1; dx <= 1; dx++)
				{
					for (int dy = -1; dy <= 1; dy++)
					{
						if (dx == 0 && dy == 0)
							continue;

						int newX = i + dx;
						int newY = j + dy;

						if (newX >= 0 && newX < n && newY >= 0 && newY < n)
						{
							if (board[newX][newY] == -1)
							{
								mineCount++;
							}
						}

					}
				}

				board[i][j] = mineCount;
			}
		}
	}
};



int main()
{


	int x, y, n, mineCount;
	MineSweeper mineSweeper;


	cout << "Enter the N of Matrix to play: ";
	cin >> n;
	cout << endl;

	cout << "Enter The Mine Count: ";
	cin >> mineCount;


	cout << "Enter the X and Y Coordinates: " << endl;
	cin >> x >> y;

	mineSweeper.InitializeBoard(n);
	mineSweeper.PlaceMine(n, mineCount, x, y);
	mineSweeper.PlaceNumbers(n, x, y);
	//mineSweeper.DisplayMine(n);
	mineSweeper.DisplayMatrix(n);




}


