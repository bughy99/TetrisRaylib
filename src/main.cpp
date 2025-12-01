#include "raylib.h"
#include "game_manager.hpp"





int main()
{
    InitWindow(400, 800, "Raylib on macOS");
    GameManager game_manager = GameManager();

    while (!WindowShouldClose())
    {
        game_manager.Update();
    }

    CloseWindow();
    return 0;
}

