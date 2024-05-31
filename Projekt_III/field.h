#ifndef FIELD_H
#define FIELD_H

#include <iostream>

// Rodzaj pola: zwykły (MAN), król (KING), brak pionka (NONE).
enum FieldType { MAN, KING, NONE };

// Kolor pionka: czarny (BLACK), biały (WHITE), brak koloru (NO_COLOR).
enum PieceColor { BLACK, WHITE, NO_COLOR };

// Klasa reprezentująca pionek
class Field {
   private:
    // Rodzaj pola
    FieldType type;

    // Kolor pionka
    PieceColor color;

   public:
    // Konstruktor domyślny inicjalizujący pionek jako brak pionka.
    Field();

    // Konstruktor inicjalizujący pionek z określonym typem i kolorem.
    Field(FieldType t, PieceColor c);

    // Metoda zwracająca typ pola.
    FieldType getType() const;

    // Metoda zwracająca kolor pionka.
    PieceColor getColor() const;

    // Metoda zwracająca symbol reprezentujący pionek.
    // white: man - w, king - W
    // black: man - b, king - B
    char getSymbol() const;

    void clearSquare();

    void promotePiece();
};

#endif