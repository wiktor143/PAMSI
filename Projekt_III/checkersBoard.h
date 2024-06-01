#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include <iostream>
#include <sstream>
#include <vector>

#include "field.h"

// Struktura przechowywująca potencjalne pola dla funkcji heurystycznej
struct Move {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

class CheckersBoard {
   private:
    // Dwuwymiarowa tablica 8x8 przechowująca obiekty klasy Piece, reprezentująca planszę do gry.
    Field board[8][8];

    // Metoda ustawiająca pionki na planszy w początkowych pozycjach.
    void initializeBoard();

   public:
    // Konstruktor domyślny, który wywołuje metodę initializeBoard w celu ustawienia początkowego
    // stanu planszy.
    CheckersBoard();

    // Metoda do wypisywania aktualnego stanu planszy w termianlu.
    void printBoard();

    void movePiece(int fromRow, int fromCol, int toRow, int toCol);

    bool isCorrectMove(int fromRow, int fromCol, int toRow, int toCol, PieceColor playerColor);

    FieldType getFieldType(int row, int col) const;

    std::vector<Move> getAllPossibleMoves(PieceColor playerColor);

    int evaluateBoard(PieceColor playerColor) const;  // Funkcja oceny stanu planszy
};
#endif