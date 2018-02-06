// Project 1 - The Maze
// David Brown 
// 28472403

#ifndef THESOLVER_HPP
#define THESOLVER_HPP

#include "MazeSolver.hpp"
#include "Maze.hpp"
#include <utility>



class theSolver: public MazeSolver
{
public: 

	theSolver();
	~theSolver();
	virtual void solveMaze(
		const Maze& maze, MazeSolution& MazeSolution);
	bool pathFinder(const Maze& maze, MazeSolution& MazeSolution, 
		std::pair<int,int> currentPair, Direction startDirection, std::vector<std::vector<int>> &mazePath);


private:
	std::pair<int, int> startPair;
	std::pair<int, int> endPair;
	std::pair<int, int> currentPair;
	int mazeHeight;
	int mazeWidth;
	Direction startDirection;
	Direction directionArray[4];
	std::vector<std::vector<int>> mazePath;
	
};


#endif
