#include "field.h"

Field::Field() : type(FieldType::NONE), color(PieceColor::NO_COLOR) {}
Field::Field(FieldType t, PieceColor c) : type(t), color(c) {}

FieldType Field::getType() const { return type; }

PieceColor Field::getColor() const { return color; }

char Field::getSymbol() const {
    if (color == BLACK) {
        return type == MAN ? 'b' : 'B';
    } else if (color == WHITE) {
        return type == MAN ? 'w' : 'W';
    }
    // Inaczej nic
    return ' ';
}

void Field::clearSquare() {
    type = NONE;
    color = NO_COLOR;
}

void Field::promotePiece() {
    if (type == MAN) {
        type = KING;
    }
}
