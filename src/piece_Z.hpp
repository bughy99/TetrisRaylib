#pragma once
#include "piece.hpp"


class Piece_Z: public Piece
{
public:
    Piece_Z() : Piece() {
        Piece::SetBlock(Vector2{3, 0}, 0);
        Piece::SetBlock(Vector2{4, 0}, 1);
        Piece::SetBlock(Vector2{4, 1}, 2);
        Piece::SetBlock(Vector2{5, 1}, 3);

        Piece::SetPivotBlock(2);
    }

private:
    
};
