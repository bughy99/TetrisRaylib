#include "playfield.hpp"
#include <iostream>

void Playfield::Draw(){
    for(int i = 0; i < cell_width; i++){
          for(int j = 0; j < cell_height; j++){
            Color col;
            if(cells[i][j] == CellState::E){
                col = GRAY;
            }
            else if(cells[i][j] == CellState::M){
                col = RED;
            }
            else{
                col = GREEN;
            }
            Vector2 pos_offset = {starting_coords.x + cell_size * i, starting_coords.y + cell_size * j};
            DrawRectangleV(pos_offset, Vector2{float(cell_size), float(cell_size)}, col);
            std::cout << cells[i][j] << " ";
        }
    }
}

void Playfield::SetCell(CellState state, Vector2 pos){
    cells[int(pos.x)][int(pos.y)] = state;
}

CellState Playfield::GetCell(Vector2 pos){
    return cells[int(pos.x)][int(pos.y)];
}

void Playfield::ClearMoving()
{
    for(int i = 0; i < cell_width; i++){
          for(int j = 0; j < cell_height; j++){
            if (cells[i][j] == CellState::M) {
                cells[i][j] = CellState::E;
            }
        }
    }
}
