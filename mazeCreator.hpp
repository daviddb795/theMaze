// Project 1 - The Maze
// David Brown 
// 28472403

#ifndef MAZECREATOR_HPP
#define MAZECREATOR_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
class mazeCreator: public MazeGenerator
{
public:
	mazeCreator();
	~mazeCreator();
	virtual void generateMaze(Maze& maze) override;
	void createMaze(Maze& maze, std::vector<std::vector<int>> 
								&mazeVector, int curRow, int curCol);
	bool isInBounds(int colX, int rowY);
	//bool checkIfWallsExist(Maze& maze, int curRow, int curCol);
private:
	int totalRows;
	int totalCols;
	int currentRow;
	int currentCol;
	int nextMove;
	int totalCells;
	int counter;
	Direction directionArray[4];
	std::random_device device;
	std::default_random_engine engine{device()};
	std::uniform_int_distribution<int> distribution{0,3};
	
};



#endif // MAZECREATOR_HPP
