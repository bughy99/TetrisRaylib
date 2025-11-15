#include "queue_manager.hpp"
#include <iostream>

std::queue<PieceType> QueueManager::GeneratePieceQueue()
{
    std::queue<PieceType> p_queue;
    for (int i = 0; i < 5; i++) {
        int random_value = GetRandomValue(0, 6); // Generate a random number between 0 and 6
        p_queue.push(static_cast<PieceType>(random_value)); // Cast the random number to PieceType
    }
    return p_queue;
}

void QueueManager::PopPiece()
{
    delete curr_piece;
    piece_queue.pop();
    if(next_piece_queue.size() == 0){
        next_piece_queue = GeneratePieceQueue();
    }

    piece_queue.push(next_piece_queue.front());
    next_piece_queue.pop();

    SpawnPiece(piece_queue.front());
}

void QueueManager::Update()
{
    if (!curr_piece->has_been_placed){
            falling_clock += GetFrameTime();
            if (falling_clock > falling_time_elapsed) {
                falling_clock = 0.0;
                curr_piece->Fall(playfield);
            }

            if (IsKeyDown(KEY_LEFT)) {
                curr_piece->Move(Vector2{-1, 0}, playfield);
            }
            if (IsKeyDown(KEY_RIGHT)) {
                curr_piece->Move(Vector2{1, 0}, playfield);
            }
            if (IsKeyDown(KEY_DOWN)) {
                falling_time_elapsed = 0.1;
            }else{
                falling_time_elapsed = 0.5;
            }
            if (IsKeyPressed(KEY_UP)) {
                curr_piece->Rotate(playfield);
            }
        } else {
            PopPiece();
        }
}

void QueueManager::SpawnPiece(PieceType p_type)
{
    switch (p_type)
    {
    case PieceType::I_PC:
        curr_piece = new Piece_I();
        break;
    case PieceType::J_PC:
        curr_piece = new Piece_J();
        break;
    case PieceType::L_PC:
        curr_piece = new Piece_L();
        break;
    case PieceType::O_PC:
        curr_piece = new Piece_O();
        break;
    case PieceType::S_PC:
        curr_piece = new Piece_S();
        break;
    case PieceType::T_PC:
        curr_piece = new Piece_T();
        break;
    case PieceType::Z_PC:
        curr_piece = new Piece_Z();
        break;
    }
}


