#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include <iostream>
#include <sstream>
#include <vector>

#include "field.h"

// Struktura przechowywująca potencjalne pola dla funkcji heurystycznej
struct Move {
    // Zmienne int są do 
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    std::vector<Move> nextCaptures; // Lista kolejnych ruchów bicia
};

class CheckersBoard {
   private:
    // Dwuwymiarowa tablica 8x8 przechowująca obiekty klasy Field, reprezentująca planszę do gry.
    Field board[8][8];

    // Metoda ustawiająca pionki na planszy w początkowych pozycjach.
    void initializeBoard();

    void findCaptureMoves(std::vector<Move> &captureMoves, int row, int col, PieceColor playerColor);

    void findNormalMoves(std::vector<Move> &moves, int row, int col, PieceColor playerColor);

    void recursiveCaptureMoves(Move &nextCaptureMoves, int newRow, int newCol, PieceColor playerColor);



   public:
    // Konstruktor domyślny, który wywołuje metodę initializeBoard w celu ustawienia początkowego
    // stanu planszy.
    CheckersBoard();

    // Metoda do wypisywania aktualnego stanu planszy w termianlu.
    void printBoard();

    void movePiece(int fromRow, int fromCol, int toRow, int toCol);

    bool isCorrectMove(int fromRow, int fromCol, int toRow, int toCol, PieceColor playerColor);

    FieldType getFieldType(int row, int col) const;

    std::vector<Move> getPossibleMoves(PieceColor playerColor);

    int evaluateBoard(PieceColor playerColor) const;  // Funkcja oceny stanu planszy
};
#endif