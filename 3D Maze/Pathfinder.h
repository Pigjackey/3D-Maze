#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "PathfinderInterface.h"

const int ROW_SIZE = 5;
const int COL_SIZE = 5;
const int DEP_SIZE = 5;

class Pathfinder : public PathfinderInterface
{
	protected:
		const int BACKGROUND = 1;
		const int WALL = 0;
		const int TEMPORARY = 2; // Used to show this path has been explored
		const int PATH = 3;
		int maze_grid[ROW_SIZE][COL_SIZE][DEP_SIZE]; // To hold values
		vector<string> solution;

	public:
		Pathfinder()
		{
			srand(time(NULL));

			for (int row = 0; row < ROW_SIZE; row++)
			{
				for (int col = 0; col < COL_SIZE; col++)
				{
					for (int dep = 0; dep < DEP_SIZE; dep++)
					{
						maze_grid[row][col][dep] = 1;
					}
				}
			}
		}
		~Pathfinder() {}

		bool importMaze(string fileName);

		void createRandomMaze();

		string toString() const;

		vector <string> solveMaze();

		bool findMazePath(int grid[ROW_SIZE][COL_SIZE][DEP_SIZE], int r, int c, int h);
};