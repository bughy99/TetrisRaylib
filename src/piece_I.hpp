#pragma once
#include "piece.hpp"


class Piece_I: public Piece
{
public:
    Piece_I() : Piece() {
        Piece::SetBlock(Vector2{3, 0}, 0);
        Piece::SetBlock(Vector2{4, 0}, 1);
        Piece::SetBlock(Vector2{5, 0}, 2);
        Piece::SetBlock(Vector2{6, 0}, 3);

        Piece::SetPivotBlock(1);
    }

private:
    
};


