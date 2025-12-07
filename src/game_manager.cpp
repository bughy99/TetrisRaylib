#include "game_manager.hpp"

Color gray = T_BLACK;

int best_score = 0;

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
            DrawScore();
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
        std::string s = "Best Score: ";
        DrawText((s + std::to_string(best_score)).c_str(), 100, 440, 20, BLACK);
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

void GameManager::DrawScore()
{
    if (score >= best_score)
    {
        best_score = score;
    }
    std::string s = std::to_string(score);
    const char *pchar = s.c_str();
    const char *text = "SCORE: ";
    std::string full_text = std::string(text) + pchar;
    DrawText(full_text.c_str(), 250, 500, 20, BLACK);
}
