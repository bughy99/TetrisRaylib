#include "queue_manager.hpp"
#include <iostream>

#include "includes.hpp"





std::queue<PieceType> QueueManager::GeneratePieceQueue()
{
    std::queue<PieceType> p_queue;
    for (int i = 0; i < 7; i++)
    {
        bool is_added = false;
        PieceType random_piece;
        while (!is_added)
        {
            random_piece = PickPiece();
            if (!isInQueue(p_queue, random_piece)){
                is_added = true;
            }
        }
        
        p_queue.push(random_piece);
    }
    return p_queue;
}

void QueueManager::PopPiece()
{
    piece_queue.pop();
    if (next_piece_queue.size() == 0)
    {
        next_piece_queue = GeneratePieceQueue();
    }

    piece_queue.push(next_piece_queue.front());
    next_piece_queue.pop();

    SpawnPiece(piece_queue.front(), curr_piece);
    has_switched = false;
}

void QueueManager::Update()
{
    if (!curr_piece->has_been_placed)
    {
        // timers
        falling_clock += GetFrameTime();
        if (falling_clock > falling_time_elapsed)
        {
            falling_clock = 0.0;
            curr_piece->Fall(playfield);
        }

        if (curr_piece->touched_down)
        {
            curr_piece->SetTouchedTime(curr_piece->GetTouchedTime() + GetFrameTime());
            if (curr_piece->GetTouchedTime() >= touched_down_time_max)
            {
                curr_piece->SetTouchedTime(0.0);
                for (int i = 0; i < 4; i++)
                {
                    playfield.SetCell(CellState::O, curr_piece->GetBlock(i));
                }
                curr_piece->~Piece();
            }
        }


        if (IsKeyDown(KEY_LEFT))
        {
            key_pressed_time += GetFrameTime();
            if (key_pressed_time < 5.0)
            {
                int curr_fps = GetFPS();
                SetTargetFPS(int(1.0 + key_pressed_time) * curr_fps);
            }
            curr_piece->Move(Vector2{-1, 0}, playfield);
        }
        else if (IsKeyReleased(KEY_LEFT))
        {
            key_pressed_time = 0.0;
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            key_pressed_time += GetFrameTime();
            if (key_pressed_time < 5.0)
            {
                int curr_fps = GetFPS();
                SetTargetFPS(int(1.0 + key_pressed_time) * curr_fps);
            }
            curr_piece->Move(Vector2{1, 0}, playfield);
        }
        else if (IsKeyReleased(KEY_RIGHT))
        {
            key_pressed_time = 0.0;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            falling_time_elapsed = 0.1;
        }
        else
        {
            falling_time_elapsed = 0.5;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X))
        {
            curr_piece->Rotate(playfield, {1, -1});
        }
        if (IsKeyPressed(KEY_Z))
        {
            curr_piece->Rotate(playfield, {-1, 1});
        }

        if (IsKeyPressed(KEY_C))
        {
            HoldPiece();
        }

        //go down instantly
        if (IsKeyPressed(KEY_SPACE))
        {
            while(curr_piece->touched_down != true)
            {
                curr_piece->Fall(playfield);
            }

            curr_piece->touched_down = true;
            curr_piece->SetTouchedTime(touched_down_time_max);
        }
    }
    else
    {
        PopPiece();
    }
}

void QueueManager::DrawQueue()
{

    float box_size = 80.0;
    Color col = T_GRAY;
    std::deque<PieceType> temp_queue(piece_queue.__get_container());

    DrawText("NEXT: ", 280.0, 15, 20, BLACK);

    for (int i = 0; i <= 4; i++)
    {
        Vector2 offset = Vector2{280.0, float(30.0 + box_size * i)};
        DrawRectangleV(offset, (Vector2){box_size, box_size}, col);
        DrawLine(offset.x, offset.y + box_size, offset.x + box_size,  offset.y + box_size, BLACK);
        DrawLine(offset.x + box_size, offset.y, offset.x + box_size,  offset.y + box_size, BLACK);
        char letter;
        switch (temp_queue[i+1])
        {
            case PieceType::I_PC:
                letter = 'I';
                break;
            case PieceType::J_PC:
                letter = 'J';
                break;
            case PieceType::L_PC:
                letter = 'L';
                break;
            case PieceType::O_PC:
                letter = 'O';
                break;
            case PieceType::S_PC:
                letter = 'S';
                break;
            case PieceType::Z_PC:
                letter = 'Z';
                break;
            case PieceType::T_PC:
                letter = 'T';
                break;
        }
        
        DrawText(std::string(1, letter).c_str(), offset.x, offset.y, 20, BLACK);
        
    }
}

void QueueManager::DrawHold()
{
    Color col = T_GRAY;
    Vector2 pos = {50.0, 550.0};
    DrawRectangleV(pos,{80.0, 80.0}, col);
    DrawText("HOLD:", 50, 530, 20, BLACK);
    char letter;
    switch (hold_pc_type)
    {
        case PieceType::I_PC:
            letter = 'I';
            break;
        case PieceType::J_PC:
            letter = 'J';
            break;
        case PieceType::L_PC:
            letter = 'L';
            break;
        case PieceType::O_PC:
            letter = 'O';
            break;
        case PieceType::S_PC:
            letter = 'S';
            break;
        case PieceType::Z_PC:
            letter = 'Z';
            break;
        case PieceType::T_PC:
            letter = 'T';
            break;
        case PieceType::NULL_PC:
            letter = '?';
            break;
    }
    DrawText(std::string(1, letter).c_str(), 50, 550, 20, BLACK);
}

void QueueManager::SpawnPiece(PieceType p_type,  Piece*& piece_ptr)
{
    delete piece_ptr;
    switch (p_type)
    {
    case PieceType::I_PC:
        piece_ptr = new Piece_I();
        break;
    case PieceType::J_PC:
        piece_ptr = new Piece_J();
        break;
    case PieceType::L_PC:
        piece_ptr = new Piece_L();
        break;
    case PieceType::O_PC:
        piece_ptr = new Piece_O();
        break;
    case PieceType::S_PC:
        piece_ptr = new Piece_S();
        break;
    case PieceType::T_PC:
        piece_ptr = new Piece_T();
        break;
    case PieceType::Z_PC:
        piece_ptr = new Piece_Z();
        break;
    }
}

void QueueManager::HoldPiece()
{
    if (!has_switched){
        std::deque<PieceType> temp_queue(piece_queue.__get_container());
        if (hold_pc_type == PieceType::NULL_PC)
        {
            hold_pc_type = temp_queue[0];
            SpawnPiece(temp_queue[1], curr_piece);
            has_switched = true;
        }
        else
        {
            SpawnPiece(hold_pc_type, curr_piece);
            hold_pc_type = temp_queue[0];

            has_switched = true;
        }
    }
}

QueueManager::~QueueManager()
{
    playfield.~Playfield();
    curr_piece->~Piece();
}

PieceType QueueManager::PickPiece()
{
    int rand_pc = GetRandomValue(0, 6);
    return static_cast<PieceType>(rand_pc);
}

bool QueueManager::isInQueue(std::queue<PieceType> p_queue, PieceType random_piece) {
    while (!p_queue.empty()) {
        if (p_queue.front() == random_piece) {
            return true; 
        }
        p_queue.pop(); 
    }
    return false; 
}