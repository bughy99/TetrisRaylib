#include "raylib.h"
#include "queue_manager.hpp"
#include "includes.hpp"

Piece_I make_new_piece();


int main()
{
    InitWindow(400, 800, "Raylib on macOS");

    Playfield playfield = Playfield(20);
    QueueManager queue_manager = QueueManager(playfield);

    Color black = T_BLACK;

    while (!WindowShouldClose())
    {
        SetTargetFPS(10);

        queue_manager.Update();
        playfield.CheckLines();

        BeginDrawing();
        ClearBackground(black);
        playfield.Draw();
        queue_manager.DrawQueue();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

Piece_I make_new_piece()
{
    Piece_I line_piece = Piece_I();

    return line_piece;
}