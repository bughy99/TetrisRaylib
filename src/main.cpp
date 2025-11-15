#include "raylib.h"
#include "queue_manager.hpp"


Piece_I make_new_piece();

int main() {
    InitWindow(400, 800, "Raylib on macOS");
    SetTargetFPS(30);

    Playfield playfield = Playfield(20);
    QueueManager queue_manager = QueueManager(playfield);



    while (!WindowShouldClose()) {
        
        queue_manager.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        playfield.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

Piece_I make_new_piece(){
    Piece_I line_piece = Piece_I();

    return line_piece;
}