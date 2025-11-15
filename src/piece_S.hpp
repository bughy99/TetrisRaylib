#pragma once
#include "piece.hpp"


class Piece_S: public Piece
{
public:
    Piece_S() : Piece() {
        Piece::SetBlock(Vector2{3, 1}, 0);
        Piece::SetBlock(Vector2{4, 1}, 1);
        Piece::SetBlock(Vector2{4, 0}, 2);
        Piece::SetBlock(Vector2{5, 0}, 3);

        Piece::SetPivotBlock(1);
    }

private:
    
};

