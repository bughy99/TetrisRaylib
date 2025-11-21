#pragma once
#include "piece.hpp"


class Piece_J: public Piece
{
public:
    Piece_J() : Piece() {
        Piece::SetBlock(Vector2{3, 1}, 0);
        Piece::SetBlock(Vector2{3, 2}, 1);
        Piece::SetBlock(Vector2{4, 2}, 2);
        Piece::SetBlock(Vector2{5, 2}, 3);

        Piece::SetPivotBlock(2);
    }

private:
    
};

