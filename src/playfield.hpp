#pragma once
#include <vector>
#include <map>
#include "raylib.h"

const int cell_width = 10;
const int cell_height = 20;

enum CellState {
    E, //Empty
    O, //Ocuppied
    M //Moving
};


class Playfield
{
public:
    Playfield(int c_s): cell_size(c_s){
        for(int i = 0; i < cell_width; i++){
            for(int j = 0; j < cell_height; j++){
                cells[i][j] = CellState::E;
            }
        }
    };
    void Draw();
    void SetCell(CellState state, Vector2 pos);
    CellState GetCell(Vector2 pos);
    void ClearMoving();
    //~Playfield();

private:
    int cell_size;
    Vector2 starting_coords = {100, 10};
    CellState cells[cell_width][cell_height];
};


