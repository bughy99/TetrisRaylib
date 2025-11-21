#pragma once
#include "piece.hpp"


class Piece_O: public Piece
{
public:
    Piece_O() : Piece() {
        Piece::SetBlock(Vector2{4, 1}, 0);
        Piece::SetBlock(Vector2{5, 1}, 1);
        Piece::SetBlock(Vector2{4, 2}, 2);
        Piece::SetBlock(Vector2{5, 2}, 3);

        Piece::SetPivotBlock(1);
    }

    virtual void Rotate(Playfield& playfield, Vector2 dir =  {1, -1}){
        return;
    };

private:
    
};
