#pragma once
#include "playfield.hpp"
#include <unordered_map>

enum States {
    OG, // original state
    R, // clockwise rotation
    L, // anticlockwise rotation
    TWO // resulting state from 2 spins
};


class Piece
{
public:
    Piece();
    Vector2 GetBlock(int i);
    void SetBlock(Vector2 pos, int i);

    virtual void SetPivotBlock(int block_ind);
    void Move(Vector2 dir, Playfield& playfield);
    virtual void Rotate(Playfield& playfield, Vector2 dir =  {1, -1}); // 1 is R (clockwise), -1 is L (anticlockwise)
    bool IsColliding(Playfield& playfield, Vector2 dir);
    void Fall(Playfield& playfield);
    virtual ~Piece();

    bool has_been_placed = false;

private:
    Vector2 block_coords[4];
    States curr_state = States::OG;
    int pivot_block;
};



