#include <raylib.h>
#include <vector>
#pragma once

void RectToPosition(Rectangle &rect, Vector2 &position);

struct Player {
    Vector2 position = {0, 0};
    Rectangle rect = {0, 0, 40, 40};
    Color color = RED;
};

struct Players {
    std::vector<Vector2> position;
    std::vector<Rectangle> rect;
    std::vector<Color> color;

    void AddPlayer(Player &player) {
        position.push_back(player.position);
        rect.push_back(player.rect);
        color.push_back(player.color);
    }

    void Draw() {
        for(auto it = rect.begin(); it != rect.end(); ++it) {
            int index = it - rect.begin();
            RectToPosition(*it, position[index]);
            DrawRectangleRec(*it, color[index]);
        }
    }

    int GetSize() {
        return position.size();
    }


};

void RectToPosition(Rectangle &rect, Vector2 &position) {
    rect.x = position.x;
    rect.y = position.y;
}
