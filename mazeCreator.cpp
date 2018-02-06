// Project 1 - The Maze
// David Brown 
// 28472403

#ifndef MAZECREATOR_CPP
#define MAZECREATOR_CPP
#include "mazeCreator.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include <random>
#include <vector>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, mazeCreator, 
											  "AMazing Generator (Required)");

mazeCreator::mazeCreator()
{	
}

mazeCreator::~mazeCreator()
{
}

void mazeCreator::generateMaze(Maze& maze)
{
	// begin the maze generator with all walls in place
	maze.addAllWalls();
	totalRows = maze.getHeight();
	totalCols = maze.getWidth();
	currentCol = 0;
	currentRow = 0;

	directionArray[0] = Direction::up;
	directionArray[1] = Direction::down;
	directionArray[2] = Direction::right;
	directionArray[3] = Direction::left;
	
	std::cout << "inside maze generator" << std::endl;
	// create vector for maze and fill with 0's
	std::vector<std::vector<int>> 
					theMaze(totalCols, std::vector<int>(totalRows));
	for (int i = 0; i < totalCols; ++i)
	{
		for(int j = 0; j < totalRows; ++j)
		{
			theMaze[i][j] = 0;
		}
	}
	
	createMaze(maze, theMaze, currentCol, currentRow);

}

bool mazeCreator::isInBounds(int colX, int rowY)
{
	if((colX < 0) || (colX > totalCols - 1))
	{
		std::cout << "col out of bounds" << std::endl;
		return false;
	}
	if((rowY < 0) || (rowY > totalRows - 1))
	{
		std::cout << "row out of bounds" << std::endl;
		return false;
	}
	
	return true;
}
// recursive function
// curCol = x and curRow = y
void mazeCreator::createMaze(Maze& maze, std::vector<std::vector<int>> 
							&mazeVector, int curCol, int curRow)
{
	
	

for(int i = 0; i < totalRows*totalCols; ++i)
{

	//std::cout << "------top of the for loop -- i =" << i << std::endl;
	mazeVector[curCol][curRow] = 1;
	int tempRow = curRow;
	int tempCol = curCol;

	// provides random #s from 1-4 to control the direction of the generator
	// ie if next move is up, down, left, right
	nextMove = distribution(engine);
	
	std::cout << "before switch " << "curCol = " << curCol <<
					" curRow = " << curRow << " nMove =" << nextMove << std::endl;
	switch (nextMove)
	{
		// move in upward direction
		case 0:
			--tempRow;	
		break;

		// move down in direction
		case 1:
			++tempRow;
		break;
		// move right in direction
		case 2:
			++tempCol;
		break;
		
		// move left in direction
		case 3:
			--tempCol;
		break;	
	} // end of switch


	// check to see if that position is in bounds
	if(isInBounds(tempCol, tempRow))
	{
		// check to see if that cell has been visited yet
		if(mazeVector[tempCol][tempRow] == 0)
		{
			maze.removeWall(curCol, curRow, directionArray[nextMove]);
			curCol = tempCol;
			curRow = tempRow;
			std::cout << "........wall removed " << std::endl;
			createMaze(maze, mazeVector, curCol, curRow);
		}
	}	
}
} // end of recursive maze function 


#endif
