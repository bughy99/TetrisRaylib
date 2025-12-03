#include "game_manager.hpp"

Color gray = T_BLACK;

void GameManager::Update()
{
    if (!game_over)
    {
        if (!playfield.game_over)
        {
            SetTargetFPS(10);

            queue_manager->Update();
            playfield.CheckLines();

            BeginDrawing();
            ClearBackground(gray);
            playfield.Draw();
            queue_manager->DrawQueue();
            queue_manager->DrawHold();
            EndDrawing();
        } else 
        {
            DeleteCurrent();
            game_over = true;
        }
    }
    else
    {

        if (IsKeyPressed(KEY_ENTER))
        {
            game_over = false;
            ReInstantiate();
        }

        BeginDrawing();
        ClearBackground(gray);
        DrawText("GAME OVER", 100, 400, 40, BLACK);
        DrawText("Press enter to try again", 100, 480, 20, BLACK);
        EndDrawing();

    }
}

void GameManager::DeleteCurrent()
{
    delete queue_manager;
    playfield.~Playfield();

}

void GameManager::ReInstantiate()
{
    playfield = Playfield(20);
    queue_manager = new QueueManager(playfield);
    game_over = false;
}
