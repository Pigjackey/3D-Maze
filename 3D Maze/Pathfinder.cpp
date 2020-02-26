#include "Pathfinder.h"

bool Pathfinder::importMaze(string file_name)
{
	cout << "importMaze from " << file_name << endl;
	ifstream file(file_name.c_str());
	if (file.is_open())
	{
		vector <int> values;
		int place = 0;
		string line;
		int value;

		while (getline(file, line))
		{
			stringstream ss(line);

			while (ss >> value)
			{
				values.push_back(value);
			}
		}

		if (values.size() != 125)
		{
			return false;
		}
		else if (values.at(0) != 1 || values.at(124) != 1)
		{
			return false;
		}
		
		for (int i = 0; i < 125; i++)
		{
			if (values.at(i) != 1 && values.at(i) != 0)
			{
				return false;
			}
		}

		for (int row = 0; row < ROW_SIZE; row++)
		{
			for (int col = 0; col < COL_SIZE; col++)
			{
				for (int dep = 0; dep < DEP_SIZE; dep++)
				{
					value = values.at(place);
					maze_grid[row][col][dep] = value;
					place++;
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}
void Pathfinder::createRandomMaze()
{
	int randVal;

	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int col = 0; col < COL_SIZE; col++)
		{
			for (int dep = 0; dep < DEP_SIZE; dep++)
			{
				randVal = rand() % 2;

				maze_grid[row][col][dep] = randVal;
			}
		}
	}

	maze_grid[0][0][0] = 1;
	maze_grid[4][4][4] = 1;
}
string Pathfinder::toString() const
{
	stringstream ss;
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int col = 0; col < COL_SIZE; col++)
		{
			for (int dep = 0; dep < DEP_SIZE; dep++)
			{
				if (dep == DEP_SIZE - 1)
				{
					ss << maze_grid[row][col][dep];
				}
				else
				{
					ss << maze_grid[row][col][dep] << " ";
				}
			}
			ss << endl;
		}

		if (row == ROW_SIZE - 1)
		{

		}
		else
		{
			ss << endl;
		}
	}
	return ss.str();
}
vector <string> Pathfinder::solveMaze()
{
	vector <string> fixMe;
	solution.clear();
	findMazePath(maze_grid, 0, 0, 0);

	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int col = 0; col < COL_SIZE; col++)
		{
			for (int dep = 0; dep < DEP_SIZE; dep++)
			{
				if (maze_grid[row][col][dep] == 3)
				{
					maze_grid[row][col][dep] = 1;
				}
				else if (maze_grid[row][col][dep] == 2)
				{
					maze_grid[row][col][dep] = 1;
				}
			}
		}
	}

	for (int i = solution.size() - 1; i >= 0; i--)
	{
		fixMe.push_back(solution.at(i));
	}
	solution.clear();
	solution = fixMe;
	fixMe.clear();
	
	return solution;
}
bool Pathfinder::findMazePath(int grid[ROW_SIZE][COL_SIZE][DEP_SIZE], int r, int c, int d)
{
	if (r < 0 || c < 0 || d < 0 || r >= ROW_SIZE || c >= COL_SIZE || d >= DEP_SIZE)
	{
		return false;      // Cell is out of bounds.
	}
	else if (grid[r][c][d] != BACKGROUND)
	{
		return false;      // Cell is on barrier or dead end.
	}
	else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && d == DEP_SIZE - 1)
	{
		grid[r][c][d] = PATH;         // Cell is on path
		solution.push_back("(" + to_string(d) + ", " + to_string(c) + ", " + to_string(r) + ")");
		return true;               // and is maze exit.
	}
	else
	{
		// Recursive case.
		// Attempt to find a path from each neighbor.
		// Tentatively mark cell as on path.
		grid[r][c][d] = PATH;
		if (findMazePath(grid, r, c, d - 1) // North
			|| findMazePath(grid, r, c, d + 1) // South
			|| findMazePath(grid, r, c - 1, d) // West
			|| findMazePath(grid, r, c + 1, d) // East
			|| findMazePath(grid, r - 1, c,	d) // Down
			|| findMazePath(grid, r + 1, c, d)) //Up
		{
			solution.push_back("(" + to_string(d) + ", " + to_string(c) + ", " + to_string(r) + ")");
			return true;
		}
		else
		{
			grid[r][c][d] = TEMPORARY;  // Dead end.
			return false;
		}
	}
}