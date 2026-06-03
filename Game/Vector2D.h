#pragma once
namespace ShatteredEngine{

    class Vector2D{
    public:
        int x, y;
        Vector2D();
        Vector2D(int X, int Y);
        bool operator ==(Vector2D vec);
    };
}