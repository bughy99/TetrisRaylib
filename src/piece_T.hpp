#pragma once
#include "piece.hpp"


class Piece_T: public Piece
{
public:
    Piece_T() : Piece() {
        Piece::SetBlock(Vector2{3, 2}, 0);
        Piece::SetBlock(Vector2{4, 2}, 1);
        Piece::SetBlock(Vector2{4, 1}, 2);
        Piece::SetBlock(Vector2{5, 2}, 3);

        Piece::SetPivotBlock(1);
    }

private:
    
};


