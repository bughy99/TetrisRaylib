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
    Z_PC,
    NULL_PC
};

// queue size is 5
class QueueManager
{
public:
    QueueManager(Playfield &p) : playfield(p)
    {
        piece_queue = GeneratePieceQueue();
        SpawnPiece(piece_queue.front(), curr_piece);

    };
    std::queue<PieceType> GeneratePieceQueue();
    void PopPiece();
    void Update();
    void DrawQueue();
    void DrawHold();
    void SpawnPiece(PieceType p_type, Piece *&piece_ptr);
    void HoldPiece();
    ~QueueManager();


private:
    Piece *curr_piece = nullptr;
    PieceType hold_pc_type = PieceType::NULL_PC;

    bool has_switched = false;

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
