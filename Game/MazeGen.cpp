#include "MazeGen.h"
#include <random>
#include <stack>
#include <iostream>
#include <fstream>
#include "Engine.h"
/*
Значения
1 - Вверх
2 - Вправо
4 - Вниз
8 - Влево
16 - Непосещённая клетка (Используется только при генерации)
*/

void GenerateMaze(std::vector<std::vector<int>>& Maze, int x1, int x2, int y1, int y2){
	int m = Maze.size(), n = Maze[0].size();
	std::random_device Seed;
	std::mt19937 RNGEngine(Seed());
	std::uniform_int_distribution<int> RNGn(x1, x2 - 1), RNGm(y1, y2 - 1), RNG4(0, 3);
	
	std::stack<ShatteredEngine::Vector2D> MapStack;
	ShatteredEngine::Vector2D RootPos(RNGn(RNGEngine), RNGm(RNGEngine));
	unsigned long int i = 0;
	// Перемещаем перрвую клетку, пока не будет найдена доступная (если её нет, то ничего не меняем)
	for(int i = x1; i < x2; i++){
		for(int j = y1; j < y2; j++){
			RootPos.x++;
			if(RootPos.x >= x2){
				RootPos.x = x1;
				RootPos.y++;
				if(RootPos.y >= y2){
					RootPos.y = y1;
				}
			}
			if((Maze[RootPos.y][RootPos.x] / 16) % 2 == 1){
				break;
			}
		}
	}
	if((Maze[RootPos.y][RootPos.x] / 16) % 2 == 0){
		return;
	}
	Maze[RootPos.y][RootPos.x] -= 16;
	MapStack.push(RootPos);

	while (!MapStack.empty()){
		ShatteredEngine::Vector2D CurPos = MapStack.top();
		short int dir = RNG4(RNGEngine); 
		// Генерируем случайное направление, после этого по часовой стрелке проверяем на продолжение ветки
		// Если ветка закончена, то ищем новое место для ответления, идя в обратном направлении
		for(int i = 0; i < 4; i++){

			dir = (dir + 1) % 4;

			if(dir == 0 && CurPos.y > y1){
				if(Maze[CurPos.y - 1][CurPos.x] / 16 == 1){
					MapStack.push(ShatteredEngine::Vector2D(CurPos.x, CurPos.y - 1));
					Maze[CurPos.y][CurPos.x] -= 1;
					Maze[CurPos.y - 1][CurPos.x] -= 20;
					break;
				}
			}
			if(dir == 1 && CurPos.x < (x2 - 1)){
				if(Maze[CurPos.y][CurPos.x + 1] / 16 == 1){
					MapStack.push(ShatteredEngine::Vector2D(CurPos.x + 1, CurPos.y));
					Maze[CurPos.y][CurPos.x] -= 2;
					Maze[CurPos.y][CurPos.x + 1] -= 24;
					break;
				}
			}
			if(dir == 2 && CurPos.y < (y2 - 1)){
				if(Maze[CurPos.y + 1][CurPos.x] / 16 == 1){
					MapStack.push(ShatteredEngine::Vector2D(CurPos.x, CurPos.y + 1));
					Maze[CurPos.y][CurPos.x] -= 4;
					Maze[CurPos.y + 1][CurPos.x] -= 17;
					break;
				}
			}
			if(dir == 3 && CurPos.x > x1){
				if(Maze[CurPos.y][CurPos.x - 1] / 16 == 1){
					MapStack.push(ShatteredEngine::Vector2D(CurPos.x - 1, CurPos.y));
					Maze[CurPos.y][CurPos.x] -= 8;
					Maze[CurPos.y][CurPos.x - 1] -= 18;
					break;
				}
			}
		}
		//Проверка и возврат
		if(MapStack.top() == CurPos){
			MapStack.pop();
		}
	}
}

std::vector<std::vector<int>> CreateBasicMapLayout(unsigned int n, unsigned int m){
	std::vector<std::vector<int>> Maze(m, std::vector<int>(n, 31));

	GenerateMaze(Maze, 0, n, 0, m);

	return Maze;
}

std::vector<std::vector<int>> CreateMapLayoutLevel1Part(unsigned int side){
	std::vector<std::vector<int>> Maze(25, std::vector<int>(25, 31));
	for(int i = 10; i < 15; i++){
		for(int j = 10; j < 15; j++){
			Maze[i][j] = 0;
		}
	}
	for(int i = 10; i < 15; i++){
		Maze[10][i] += 1;
		Maze[i][14] += 2;
		Maze[14][i] += 4;
		Maze[i][10] += 8;
	}
	
	//GenerateMaze(Maze);

	switch (side){
	case 0: // Вверхняя комната
		Maze[10][12] -= 1;
		Maze[9][12]  -= 4;
		Maze[24][12] -= 4;
		break;
	case 1: // Правая комната
		Maze[12][14] -= 2;
		Maze[12][15] -= 8;
		Maze[12][0]  -= 8;
		break;
	case 2: // Нижняя комната
		Maze[14][12] -= 4;
		Maze[15][12] -= 1;
		Maze[0][12]  -= 1;
		break;
	case 3: // Левая комната
		Maze[12][10] -= 8;
		Maze[12][9]  -= 2;
		Maze[12][24] -= 2;
		break;
	default:
		break;
	}
	return Maze;
}

std::vector<std::vector<int>> CreateLevelMap1(){
	std::vector<std::vector<int>> map(25, std::vector<int>(63, -1));
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			map[i][j] = 31;
		}
		for(int j = 38; j < 63; j++){
			map[i][j] = 31;
		}
	}
	for(int i = 10; i < 15; i++){
		for(int j = 10; j < 15; j++){
			map[i][j] = 0;
		}
		for(int j = 48; j < 53; j++){
			map[i][j] = 0;
		}
	}
	map[13][12] += 1;
	map[12][11] += 2;
	map[11][12] += 4;
	map[12][13] += 8;

	map[13][50] += 1;
	map[12][49] += 2;
	map[11][50] += 4;
	map[12][51] += 8;

	for(int i = 10; i < 15; i++){
		map[10][i] += 1;
		map[i][14] += 2;
		map[14][i] += 4;
		map[i][10] += 8;

		map[10][i + 38] += 1;
		map[i][52]      += 2;
		map[14][i + 38] += 4;
		map[i][48]      += 8;
	}
	GenerateMaze(map, 0, 25, 0, 25);
	GenerateMaze(map, 38, 63, 0, 25);

	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			map[i][j] += 16;
		}
		for(int j = 38; j < 63; j++){
			map[i][j] += 16;
		}
	}

	for(int i = 10; i < 15; i++){
		for(int j = 10; j < 15; j++){
			map[i][j] -= 16;
		}
		for(int j = 48; j < 53; j++){
			map[i][j] -= 16;
		}
	}

	map[12][10] -= 8;
	map[12][9]  -= 2;
	map[12][24] -= 2;

	map[12][52] -= 2;
	map[12][53] -= 8;
	map[12][38] -= 8;

	for(int j = 25; j < 28; j++){
		map[11][j] = 1;
		map[12][j] = 0;
		map[13][j] = 4;

		map[11][j + 10] = 1;
		map[12][j + 10] = 0;
		map[13][j + 10] = 4;
	}
	map[11][25] += 8;
	map[13][25] += 8;
	map[11][27] += 2;
	map[13][27] += 2;

	map[11][35] += 8;
	map[13][35] += 8;
	map[11][37] += 2;
	map[13][37] += 2;
	for(int i = 10; i < 15; i++){
		for(int j = 28; j < 35; j++){
			map[i][j] = 0;
		}
	}
	for(int i = 29; i < 34; i++){
		map[9][i]  = 1;
		map[15][i] = 0;
	}
	for(int i = 15; i < 25; i++){
		map[i][30] = 8;
		map[i][31] = 0;
		map[i][32] = 2;
	}
	map[9][33] += 2;
	map[9][29] += 8; 
	map[14][34] = 4;
	map[14][28] = 4;

	for(int i = 10; i < 15; i++){
		if(i == 12){
			continue;
		}
		map[i][34] += 2;
		map[i][28] += 8;
	}
	map[10][28] += 1;
	map[10][34] += 1;
	map[14][29] += 4;
	map[14][33] += 4;

	map[15][30] += 4;
	map[15][31] += 4;
	map[15][32] += 4;

	for(int i = 10; i < 15; i++){
		for(int j = 10; j < 15; j++){
			map[i][j] += 32;
		}
		for(int j = 48; j < 53; j++){
			map[i][j] += 32;
		}
	}
	for(int i = 0; i < 25; i++){
		for(int j = 25; j < 38; j++){
			if(map[i][j] == -1){
				map[i][j] = 15;	
			}
			map[i][j] += 32;
		}
	}
	map[15][33] = -2;
	map[15][29] = -2;
	map[12][12] = -3;
	map[12][50] = -3;
	return map;
}