#pragma once
#include <vector>
std::vector<std::vector<int>> CreateBasicMapLayout(unsigned int n, unsigned int m);
void GenerateMaze(std::vector<std::vector<int>>& Maze, int x1, int x2, int y1, int y2);
std::vector<std::vector<int>> CreateLevelMap1();
std::vector<std::vector<int>> CreateMapLayoutLevel1Part(unsigned int side);