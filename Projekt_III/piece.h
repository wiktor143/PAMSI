#ifndef PIECE_H
#define PIECE_H

#include <iostream>

// Rodzaj pionka: zwykły (MAN), król (KING), brak pionka (NONE).
enum PieceType { MAN, KING, NONE };

// Kolor pionka: czarny (BLACK), biały (WHITE), brak koloru (NO_COLOR).
enum PieceColor { BLACK, WHITE, NO_COLOR };


// Klasa reprezentująca pionek
class Piece {
   private:
    // Rodzaj pionka
    PieceType type;

    // Kolor pionka
    PieceColor color;

   public:

    // Konstruktor domyślny inicjalizujący pionek jako brak pionka.
    Piece();

    // Konstruktor inicjalizujący pionek z określonym typem i kolorem.
    Piece(PieceType t, PieceColor c);

    // Metoda zwracająca typ pionka.
    PieceType getType() const;

    // Metoda zwracająca kolor pionka.
    PieceColor getColor() const;

    // Metoda zwracająca symbol reprezentujący pionek.
    // white: man - w, king - W
    // black: man - b, king - B 
    char getSymbol() const;

    void clearSquare();
};

#endif