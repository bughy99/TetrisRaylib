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

void Piece::SetPivotBlock(int block_ind)
{
    pivot_block = block_ind;
}

void Piece::Move(Vector2 dir, Playfield &playfield)
{
    if (!IsColliding(playfield, dir)){
        playfield.ClearMoving();
        for(int i = 0; i < 4; i++){
                block_coords[i] = Vector2{(block_coords[i].x + dir.x), block_coords[i].y};
                playfield.SetCell(CellState::M, block_coords[i]);
        }
    }
}

void Piece::Rotate(Playfield& playfield, Vector2 dir)
{
    Vector2 pivot_point = GetBlock(pivot_block);
    std::array<Vector2, 4> rotates;
    for (int i = 0; i < 4; i++) {
        Vector2 rel = Vector2{block_coords[i].x - pivot_point.x, block_coords[i].y - pivot_point.y}; 
        Vector2 rotated = { rel.y * dir.y, rel.x * dir.x }; // 90° clockwise
        if (!IsColliding(playfield, rotated)){
            rotates[i] = rotated;
        }else {
            return;
        }
    }
    playfield.ClearMoving();
    for (int i = 0; i < 4; i++) {
        Vector2 rotated = rotates[i];
        block_coords[i] = Vector2{pivot_point.x + rotated.x, pivot_point.y + rotated.y};
        playfield.SetCell(CellState::M, block_coords[i]);
    }
}

bool Piece::IsColliding(Playfield& playfield, Vector2 dir) {
    for(int i = 0; i < 4; i++){
        if (((block_coords[i].x + dir.x) < 0) || ((block_coords[i].x + dir.x) >= cell_width ) 
        || ((playfield.GetCell(Vector2{block_coords[i].x + dir.x, block_coords[i].y + dir.y}) == CellState::O))){
                return true;
        }
    }


    return false;
}

void Piece::Fall(Playfield& playfield) {
    playfield.ClearMoving();
    bool is_colliding = false;

    for (int i = 0; i < 4; i++){
        if (block_coords[i].y + 1 >= cell_height) {
            is_colliding = true;
        }
        if (playfield.GetCell(Vector2{block_coords[i].x, block_coords[i].y + 1}) == CellState::O) {
            is_colliding = true;
        }
    }

    if (!is_colliding) {

        for (int i = 0; i < 4; i++){
            block_coords[i].y += 1;
            playfield.SetCell(CellState::M, block_coords[i]);
        }

    } else {
        for (int i = 0; i < 4; i++){
            playfield.SetCell(CellState::O, block_coords[i]);
        }
        Piece::~Piece();
    }

}

Piece::~Piece() {
    has_been_placed = true;
}
