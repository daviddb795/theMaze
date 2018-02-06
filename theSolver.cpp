// Project 1 - The Maze
// David Brown 
// 28472403

#ifndef THESOLVER_CPP
#define THESOLVER_CPP
#include "theSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <iostream>
#include <ics46/factory/DynamicFactory.hpp>
#include <cmath>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, theSolver, 
										   "AMazing Solution (Required)");

theSolver::theSolver()
{
}
theSolver::~theSolver()
{
}

void theSolver::solveMaze(const Maze& maze, MazeSolution& MazeSolution)
{
  MazeSolution.restart();
  mazeHeight = MazeSolution.getHeight();
  mazeWidth = MazeSolution.getWidth();
  startPair = MazeSolution.getStartingCell();

  std::vector<std::vector<int>> 
					mazePath(mazeWidth, std::vector<int>(mazeHeight));
  
directionArray[0] = Direction::up;
directionArray[1] = Direction::down;
directionArray[2] = Direction::right;
directionArray[3] = Direction::left;

 for (int i = 0; i < mazeWidth; ++i)
	{
		for(int j = 0; j < mazeHeight; ++j)
		{
			mazePath[i][j] = 0;
		}
	}

for(int i =0; i < 4; ++i)
{
	startDirection = directionArray[i];
	pathFinder(maze, MazeSolution, startPair, startDirection, mazePath);
}
  
}

bool theSolver::pathFinder(const Maze& maze, MazeSolution& MazeSolution, 
		std::pair<int,int> currentPair, Direction pathDirection, std::vector<std::vector<int>> &mazePath)
{
	std::cout << "BEGIN " << currentPair.first << " " 
							<< currentPair.second << std::endl;
	// the solution has been found 
	if(currentPair == MazeSolution.getEndingCell())
	{
		std::cout << "inside end " << std::endl;
		return true;
	}

	// check to make sure the next step is not out of bounds 
	if((currentPair.first > mazeWidth) || (currentPair.first < 0)
		|| (currentPair.second > mazeHeight)
		|| (currentPair.second < 0)) 
	{
		std::cout << "inside out of bounds " << std::endl;
		return false;

	}
	
	std::cout << "above wallExists " << std::endl;
	// check to see if there is a wall blocking the next step of solution 
	if(maze.wallExists(currentPair.first, currentPair.second, 
					   pathDirection)) 
	{
		std::cout << "A wall wallExists " << std::endl;

		return false;
	}
	
	if((mazePath[currentPair.first][abs(currentPair.second - 1)] == 1 )
		&&(pathDirection == Direction::up))
	{
		std::cout << "we have been to this cell" << std::endl;
		return false;
	}
	if((mazePath[currentPair.first][currentPair.second + 1] == 1 )
		&&(pathDirection == Direction::down))
	{
		std::cout << "we have been to this cell" << std::endl;
		return false;
	}
	if((mazePath[currentPair.first + 1][currentPair.second] == 1 )
		&&(pathDirection == Direction::right))
	{
		std::cout << "we have been to this cell" << std::endl;
		return false;
	}
	if((mazePath[abs(currentPair.first - 1)][currentPair.second] == 1 )
		&&(pathDirection == Direction::left))
	{
		std::cout << "we have been to this cell" << std::endl;
		return false;
	}
	// add to path if above three if statements fail
	MazeSolution.extend(pathDirection);
	std::cout << "just extend the path " << std::endl;
	
	mazePath[currentPair.first][currentPair.second] = 1;
	
	if(pathDirection == Direction::up)
		{
			--currentPair.second;
			std::cout << "direction up " << std::endl;
		}
	if(pathDirection == Direction::down)
		{
			++currentPair.second;
			std::cout << "direction down " << std::endl;
		}
	if(pathDirection == Direction::right)
	{
		++currentPair.first;
		std::cout << "direction right " << std::endl;
	}
	if(pathDirection == Direction::left)
	{
		--currentPair.first;
		std::cout << "direction left "<< std::endl;
	}
	
	// go up
	std::cout << "FIRST " << currentPair.first << currentPair.second << std::endl;
	if(pathFinder(maze, MazeSolution, 
		std::make_pair(currentPair.first,currentPair.second), Direction::up, mazePath) == true)
	{	
		return true;
	}
	
	// go down
	std::cout << "SECOND " << currentPair.first << currentPair.second << std::endl;
	if(pathFinder(maze, MazeSolution, 
		std::make_pair(currentPair.first,currentPair.second), Direction:: down, mazePath) == true)
	{
		return true;
	}

	// go right 
	std::cout << "THIRD " << currentPair.first << currentPair.second << std::endl;
	if(pathFinder(maze, MazeSolution, 
		std::make_pair(currentPair.first,currentPair.second), Direction::right, mazePath) == true)
	{
		return true;
	}

	// go left  
	std::cout << "FOURTH " << currentPair.first << currentPair.second << std::endl;
	if(pathFinder(maze, MazeSolution, 
		std::make_pair(currentPair.first,currentPair.second), Direction::left, mazePath) == true)
	{
		return true;
	}
	
	std::cout << "about to back up " << std::endl;
	MazeSolution.backUp();
	std::cout << "after back up " << std::endl;
	return false;	


}
#endif
