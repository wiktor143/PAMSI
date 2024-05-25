#include "piece.h"

Piece::Piece()
    : type(PieceType::NONE), color(PieceColor::NO_COLOR), status(PieceStatus::DISACTIVE) {}
Piece::Piece(PieceType t, PieceColor c, PieceStatus s) : type(t), color(c), status(s) {}

PieceType Piece::getType() const { return type; }

PieceColor Piece::getColor() const { return color; }

PieceStatus Piece::getStatus() const { return status; }

char Piece::getSymbol() const {
    if (color == BLACK) {
        return type == MAN ? 'b' : 'B';
    } else if (color == WHITE) {
        return type == MAN ? 'w' : 'W';
    }
    // Inaczej nic 
    return ' ';
}
