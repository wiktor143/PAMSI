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
    // Zwraca FieldType: MAN, KING lub NONE.
    FieldType getType() const;

    // Metoda zwracająca kolor pionka.
    // Zwraca PieceColor: BLACK, WHITE lub NO_COLOR.
    PieceColor getColor() const;

    // Metoda zwracająca symbol reprezentujący pionek.
    // Zwraca 'w' dla białego pionka, 'W' dla białej damki,
    // 'b' dla czarnego pionka, 'B' dla czarnej damki,
    // oraz ' ' dla pustego pola.
    char getSymbol() const;

    // Metoda czyszcząca pole, ustawiając typ na NONE i kolor na NO_COLOR.
    void clearSquare();

    // Metoda promująca pionek na damkę (króla), zmieniając jego typ na KING.
    void promotePiece();
};

#endif