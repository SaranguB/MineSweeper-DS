#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
using namespace std;

enum class PlayerState
{
	Playing,
	Won,
	Lose,
};

class MineSweeper
{
private:
	vector <vector<int>> board;
	vector <vector<int>> state;

	PlayerState playerState;

	void Reveal(int n, int x, int y)
	{

		if (x < 0 || x >= n || y < 0 || y >= n || state[x][y] == 1 || board[x][y] == -1)
		{
			

			return;
		}
		


		state[x][y] = 1;

		if (board[x][y] > 0)
			return;


		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (dx == 0 && dy == 0)
					continue;

				int newX = x + dx;
				int newY = y + dy;

				Reveal(n, newX, newY);

			}
		}
	}

public:

	void InitializeBoard(int n)
	{
		board.clear();  
		state.clear();  
		board.resize(n, vector<int>(n, 0));
		state.resize(n, vector<int>(n, 0));
		SetPlayerState(PlayerState::Playing);
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
				else if (board[i][j] != 0)
				{
					cout << " " << board[i][j] << " ";
				}
				else
				{
					cout << " 0 ";
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

	void DisplayPlayingMatrix(int n)
	{
		for (int i = 0;i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << " | ";
				if (state[i][j] == 0)
				{
					cout << " . ";
				}
				else if (board[i][j] == -1)
				{
					cout << " * ";
				}
				else if(board[i][j] == 0)
				{
					cout << " 0 ";
				}
				else
				{
					cout << " " << board[i][j] << " ";
				}
			}
			cout << " | " << endl << endl;
		}
	}

	void PlaceNumbers(int n, int chooseX, int chooseY)
	{
		int mineCount = 0;

		state[chooseX][chooseY] = 1;

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

	void Gameplay(int n, int x, int y)
	{
		if (state[x][y] == 1)
			return;

		if (board[x][y] == 0)
		{
			Reveal(n, x, y);
		}

		state[x][y] = 1;



		if (board[x][y] == -1)
		{
			SetPlayerState(PlayerState::Lose);
			return;
		}

		

		int totalCells = n * n;
		int openedCells = 0;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (state[i][j] == 1 || board[i][j] == -1)
					openedCells++;
			}
		}

		if (openedCells == totalCells)
		{
			SetPlayerState(PlayerState::Won);
		}

	}

	

	void SetPlayerState(PlayerState state)
	{
		playerState = state;
	}

	PlayerState GetPlayerState()
	{
		return playerState;
	}
};



int main()
{

	char input;

	int x, y, n, mineCount;
	MineSweeper mineSweeper;

	do
	{
		
		cout << "Enter the N of Matrix to play: ";
		cin >> n;
		cout << endl;

		cout << "Enter The Mine Count: ";
		cin >> mineCount;

		mineSweeper.InitializeBoard(n);


		do
		{
			cout << "Enter the X and Y Coordinates (0 to " << n - 1 << "): " << endl;
			cin >> x >> y;
			if (x < 0 || x >= n || y < 0 || y >= n) {
				cout << "Invalid coordinates. Please enter values between 0 and " << n - 1 << "." << endl;
			}
		} while (x < 0 || x >= n || y < 0 || y >= n);




		mineSweeper.PlaceMine(n, mineCount, x, y);
		mineSweeper.PlaceNumbers(n, x, y);


		mineSweeper.DisplayPlayingMatrix(n);

		while (mineSweeper.GetPlayerState() == PlayerState::Playing)
		{
			cout << "Enter the X and Y Coordinates : " << endl;
			cin >> x >> y;

			if (x < 0 || x >= n || y < 0 || y >= n) {
				cout << "Invalid coordinates. Please enter values between 0 and " << n - 1 << "." << endl;
				continue;
			}

			mineSweeper.Gameplay(n, x, y);

			if (mineSweeper.GetPlayerState() == PlayerState::Lose)
			{
				cout << "You have Lost" << endl;
				mineSweeper.DisplayMatrix(n);
			}
			else if (mineSweeper.GetPlayerState() == PlayerState::Won)
			{
				cout << "You Have Won" << endl;
				mineSweeper.DisplayMatrix(n);
			}
			else
			{
				mineSweeper.DisplayPlayingMatrix(n);
			}
		}

		cout << "Enter Y to Play Again or Enter N to Exit: ";
		cin >> input;

	} while (input == 'y' || input == 'Y');



}


