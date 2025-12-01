#include "game_manager.hpp"

Color gray = T_BLACK;

void GameManager::Update()
{
    if (!playfield.game_over)
    {
        SetTargetFPS(10);

        queue_manager.Update();
        playfield.CheckLines();

        BeginDrawing();
        ClearBackground(gray);
        playfield.Draw();
        queue_manager.DrawQueue();
        EndDrawing();
    }
    else
    {
        BeginDrawing();
        ClearBackground(gray);
        DrawText("GAME OVER", 100, 400, 40, BLACK);
        EndDrawing();
    }
}
