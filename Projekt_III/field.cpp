#include "field.h"

// Konstruktor domyślny inicjalizujący pionek jako brak pionka (NONE) i brak koloru (NO_COLOR).
Field::Field() : type(FieldType::NONE), color(PieceColor::NO_COLOR) {}

// Konstruktor inicjalizujący pionek z określonym typem (t) i kolorem (c).
Field::Field(FieldType t, PieceColor c) : type(t), color(c) {}

// Metoda zwracająca typ pola (pionka).
// Zwraca wartość typu FieldType: MAN, KING lub NONE.
FieldType Field::getType() const { return type; }

// Metoda zwracająca kolor pionka.
// Zwraca wartość typu PieceColor: BLACK, WHITE lub NO_COLOR.
PieceColor Field::getColor() const { return color; }

// Metoda zwracająca symbol reprezentujący pionek.
// Zwraca:
// 'b' dla czarnego pionka,
// 'B' dla czarnego króla,
// 'w' dla białego pionka,
// 'W' dla białego króla,
// ' ' dla pustego pola.
char Field::getSymbol() const {
    if (color == BLACK) {
        return type == MAN ? 'b' : 'B';
    } else if (color == WHITE) {
        return type == MAN ? 'w' : 'W';
    }
    // W przeciwnym razie zwraca pusty znak
    return ' ';
}

// Metoda czyszcząca pole, ustawiając typ na NONE i kolor na NO_COLOR.
void Field::clearSquare() {
    type = NONE;
    color = NO_COLOR;
}

// Metoda promująca pionek na damkę (króla), zmieniając jego typ na KING.
void Field::promotePiece() {
    if (type == MAN) {
        type = KING;
    }
}
