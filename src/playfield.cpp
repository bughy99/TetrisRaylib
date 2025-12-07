#include "playfield.hpp"
#include <iostream>
#include "includes.hpp"

int score = 0;

void Playfield::CheckLines()
{

    for (int i = 0; i < cell_width; i++)
    {
        if (cells[i][0] == CellState::O)
            {
                game_over = true;
                break;
            }
    }

    for (int j = 1; j < cell_height; j++)
    {
        bool is_full = true;
        for (int i = 0; i < cell_width; i++)
        {
            if (cells[i][j] != CellState::O)
            {
                is_full = false;
                break;
            }
        }
        if (is_full)
        {
            ClearLine(j);
            score += 40;
        }
    }
}

void Playfield::ClearLine(int y_index)
{
    for (int y = y_index; y > 0; y--)
    {
        for (int x = 0; x < cell_width; x++)
        {
            cells[x][y] = cells[x][y - 1];
        }
    }

    for (int x = 0; x < cell_width; x++)
    {
        cells[x][0] = CellState::E;
    }
}

void Playfield::Draw()
{
    for (int i = 0; i < cell_width; i++)
    {
        for (int j = 1; j < cell_height; j++)
        {
            Color col;
            if (cells[i][j] == CellState::E)
            {
                col = T_GRAY;
            }
            else if (cells[i][j] == CellState::M)
            {
                col = T_LPURP;
            }
            else
            {
                col = T_MAGENTA;
            }
            Vector2 pos_offset = {starting_coords.x + cell_size * i, starting_coords.y + cell_size * j};
            DrawRectangleV(pos_offset, Vector2{float(cell_size), float(cell_size)}, col);
            DrawLine(pos_offset.x, pos_offset.y + cell_size, pos_offset.x + cell_size,  pos_offset.y + cell_size, BLACK);
            DrawLine(pos_offset.x+ cell_size, pos_offset.y, pos_offset.x + cell_size,  pos_offset.y + cell_size, BLACK);
        }
    }
}

void Playfield::SetCell(CellState state, Vector2 pos)
{
    cells[int(pos.x)][int(pos.y)] = state;
}

CellState Playfield::GetCell(Vector2 pos)
{
    return cells[int(pos.x)][int(pos.y)];
}

void Playfield::ClearMoving()
{
    for (int i = 0; i < cell_width; i++)
    {
        for (int j = 1; j < cell_height; j++)
        {
            if (cells[i][j] == CellState::M)
            {
                cells[i][j] = CellState::E;
            }
        }
    }
}

Playfield::~Playfield()
{
    score = 0;
}

