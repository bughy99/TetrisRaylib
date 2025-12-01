#include "piece.hpp"

Piece::Piece()
{
}

Vector2 Piece::GetBlock(int i)
{
    return block_coords[i];
}

void Piece::SetBlock(Vector2 pos, int i)
{
    block_coords[i] = pos;
}

void Piece::SetTouchedTime(float t)
{
    touched_down_time = t;
}

float Piece::GetTouchedTime()
{
    return touched_down_time;
}

void Piece::SetPivotBlock(int block_ind)
{
    pivot_block = block_ind;
}

void Piece::Move(Vector2 dir, Playfield &playfield)
{
    if (!IsColliding(playfield, dir))
    {
        playfield.ClearMoving();
        for (int i = 0; i < 4; i++)
        {
            block_coords[i] = Vector2{(block_coords[i].x + dir.x), block_coords[i].y};
            playfield.SetCell(CellState::M, block_coords[i]);
        }
    }
}

void Piece::Rotate(Playfield &playfield, Vector2 dir)
{
    Vector2 pivot_point = GetBlock(pivot_block);
    std::array<Vector2, 4> rotates;
    std::array<Vector2, 5> wall_kicks = {
        Vector2{0, 0}, Vector2{-1, 0}, Vector2{1, 0}, Vector2{0, -1}, Vector2{0, 1}};

    for (int i = 0; i < 4; i++)
    {
        Vector2 rel = Vector2{block_coords[i].x - pivot_point.x, block_coords[i].y - pivot_point.y};
        rotates[i] = Vector2{rel.y * dir.y, rel.x * dir.x}; // 90° clockwise or counterclockwise
    }

    for (const auto &kick : wall_kicks)
    {
        bool can_rotate = true;
        for (int i = 0; i < 4; i++)
        {
            Vector2 rotated = Vector2{pivot_point.x + rotates[i].x + kick.x, pivot_point.y + rotates[i].y + kick.y};
            if (rotated.x < 0 ||
                rotated.x >= cell_width ||
                rotated.y < 0 ||
                rotated.y >= cell_height ||
                playfield.GetCell(rotated) == CellState::O)
            {
                can_rotate = false;
                break;
            }
        }

        if (can_rotate)
        {
            playfield.ClearMoving();
            for (int i = 0; i < 4; i++)
            {
                block_coords[i] = Vector2{pivot_point.x + rotates[i].x + kick.x, pivot_point.y + rotates[i].y + kick.y};
                playfield.SetCell(CellState::M, block_coords[i]);
            }
            return;
        }
    }
}

bool Piece::IsColliding(Playfield &playfield, Vector2 dir)
{
    for (int i = 0; i < 4; i++)
    {
        if (((block_coords[i].x + dir.x) < 0) || ((block_coords[i].x + dir.x) >= cell_width) || ((playfield.GetCell(Vector2{block_coords[i].x + dir.x, block_coords[i].y + dir.y}) == CellState::O)))
        {
            return true;
        }
    }

    return false;
}

void Piece::Fall(Playfield &playfield)
{

    bool is_colliding = false;

    for (int i = 0; i < 4; i++)
    {
        if (block_coords[i].y + 1 > cell_height - 1)
        {
            is_colliding = true;
        }
        if (playfield.GetCell(Vector2{block_coords[i].x, block_coords[i].y + 1}) == CellState::O)
        {
            is_colliding = true;
        }
    }

    if (!is_colliding)
    {
        touched_down = false;
        playfield.ClearMoving();
        for (int i = 0; i < 4; i++)
        {
            block_coords[i].y += 1;
            playfield.SetCell(CellState::M, block_coords[i]);
        }
    }
    else
    {
        touched_down = true;
    }
}

Piece::~Piece()
{
    has_been_placed = true;
}
