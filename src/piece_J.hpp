#pragma once
#include "piece.hpp"


class Piece_J: public Piece
{
public:
    Piece_J() : Piece() {
        Piece::SetBlock(Vector2{3, 0}, 0);
        Piece::SetBlock(Vector2{3, 1}, 1);
        Piece::SetBlock(Vector2{4, 1}, 2);
        Piece::SetBlock(Vector2{5, 1}, 3);

        Piece::SetPivotBlock(2);
    }

private:
    
};

