#pragma once
#include "piece.hpp"


class Piece_L: public Piece
{
public:
    Piece_L() : Piece() {
        Piece::SetBlock(Vector2{3, 2}, 0);
        Piece::SetBlock(Vector2{4, 2}, 1);
        Piece::SetBlock(Vector2{5, 2}, 2);
        Piece::SetBlock(Vector2{5, 1}, 3);

        Piece::SetPivotBlock(1);
    }

private:
    
};

