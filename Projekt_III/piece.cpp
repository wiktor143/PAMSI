#include "piece.h"

Piece::Piece()
    : type(PieceType::NONE), color(PieceColor::NO_COLOR){}
Piece::Piece(PieceType t, PieceColor c) : type(t), color(c){}

PieceType Piece::getType() const { return type; }

PieceColor Piece::getColor() const { return color; }

char Piece::getSymbol() const {
    if (color == BLACK) {
        return type == MAN ? 'b' : 'B';
    } else if (color == WHITE) {
        return type == MAN ? 'w' : 'W';
    }
    // Inaczej nic 
    return ' ';
}

void Piece::clearSquare() {
    type = NONE;
    color = NO_COLOR;
}
