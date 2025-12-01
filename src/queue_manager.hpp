#pragma once
#include "piece_I.hpp"
#include "piece_J.hpp"
#include "piece_L.hpp"
#include "piece_O.hpp"
#include "piece_S.hpp"
#include "piece_T.hpp"
#include "piece_Z.hpp"
#include "queue"
#include "random"
#include "playfield.hpp"

enum PieceType
{
    I_PC,
    J_PC,
    L_PC,
    O_PC,
    S_PC,
    T_PC,
    Z_PC
};

// queue size is 5
class QueueManager
{
public:
    QueueManager(Playfield &p) : playfield(p)
    {
        piece_queue = GeneratePieceQueue();
        SpawnPiece(piece_queue.front());

        texture_1 = LoadTexture("../tetris_piece1.png");
        texture_2 = LoadTexture("../tetris_piece2.png");
        texture_3 = LoadTexture("../tetris_piece3.png");
        texture_4 = LoadTexture("../tetris_piece4.png");
        texture_5 = LoadTexture("../tetris_piece5.png");
        texture_6 = LoadTexture("../tetris_piece6.png");
        texture_7 = LoadTexture("../tetris_piece7.png");

    };
    std::queue<PieceType> GeneratePieceQueue();
    void PopPiece();
    void Update();
    void DrawQueue();
    void SpawnPiece(PieceType p_type);

    Texture texture_1;
    Texture texture_2;
    Texture texture_3;
    Texture texture_4;
    Texture texture_5;
    Texture texture_6 ;
    Texture texture_7;

private:
    Piece *curr_piece = nullptr;
    std::queue<PieceType> piece_queue;
    std::queue<PieceType> next_piece_queue;
    Playfield &playfield;

    // timers
    float falling_clock = 0.0;
    float falling_time_elapsed = 0.5;
    float key_pressed_time = 0.0;
    float touched_down_time_max = 3.0;

    PieceType PickPiece();
    bool isInQueue(std::queue<PieceType> p_queue, PieceType random_piece);
};
