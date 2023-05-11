#include <raylib.h>
#include <vector>
#include "players.cpp"
#pragma once


struct Enemy {
    float health = 100;
    Vector2 position = {0, 0};
    Rectangle rect = {position.x, position.y, 20, 20};
    Color color = DARKBLUE;
};


struct Enemies {
    std::vector<float> health;
    std::vector<Vector2> position;
    std::vector<Rectangle> rect;
    std::vector<Color> color;


    void AddEnemy(Enemy &enemy) {
        this->health.push_back(enemy.health);
        this->position.push_back(enemy.position);
        this->rect.push_back(enemy.rect);
        this->color.push_back(enemy.color);
    }

    void Draw() {
        for(auto it = rect.begin(); it != rect.end(); ++it) {
            int index = it - rect.begin();
            RectToPosition(*it, position[index]);
            DrawRectangleRec(*it, color[index]);
        }
    }

    int GetSize() {
        return health.size();
    }
};



