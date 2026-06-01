#include "Engine.h"

ShatteredEngine::Vector2D::Vector2D(){
    x = 0;
    y = 0;
}

ShatteredEngine::Vector2D::Vector2D(int X, int Y){
    x = X;
    y = Y;
}

bool ShatteredEngine::Vector2D::operator ==(ShatteredEngine::Vector2D vec){
		if(vec.x == x && vec.y == y){
			return true;
		}
		return false;
	}