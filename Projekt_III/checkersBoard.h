#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include <iostream>
#include <sstream>
#include <vector>

#include "field.h"

// Struktura przechowywująca potencjalne pola dla funkcji heurystycznej
struct Move {
    int fromRow;                     // Wiersz początkowy ruchu
    int fromCol;                     // Kolumna początkowa ruchu
    int toRow;                       // Wiersz końcowy ruchu
    int toCol;                       // Kolumna końcowa ruchu
    std::vector<Move> nextCaptures;  // Lista kolejnych ruchów bicia
};

class CheckersBoard {
   private:
    // Dwuwymiarowa tablica 8x8 przechowująca obiekty klasy Field, reprezentująca planszę do gry.
    Field board[8][8];

    // Metoda ustawiająca pionki na planszy w początkowych pozycjach.
    void initializeBoard();

    // Metoda znajdująca możliwe ruchy bicia dla danego pionka.
    // Parametry:
    // - captureMoves: wektor, do którego dodawane są ruchy bicia.
    // - row, col: pozycja pionka
    // - playerColor: kolor pionka
    void findCaptureMoves(std::vector<Move> &captureMoves, int row, int col, PieceColor playerColor);

    // Metoda znajdująca możliwe zwykłe ruchy dla danego pionka.
    // Parametry:
    // - moves: wektor, do którego dodawane są zwykłe ruchy
    // - row, col: pozycja pionka
    // - playerColor: kolor pionka
    void findNormalMoves(std::vector<Move> &moves, int row, int col, PieceColor playerColor);

    // Metoda rekurencyjnie znajdująca kolejne możliwe ruchy bicia.
    // Parametry:
    // - nextCaptureMoves: struktura przechowująca możliwe ruchy bicia
    // - newRow, newCol: nowa pozycja pionka po wykonaniu ruchu
    // - playerColor: kolor pionka
    void recursiveCaptureMoves(Move &nextCaptureMoves, int newRow, int newCol, PieceColor playerColor);

    // Funkcja sprawdzająca, czy pionek jest bezpieczny (przy krawędzi planszy).
    // Parametry:
    // - row, col: pozycja pionka.
    // Zwraca true, jeśli pionek jest bezpieczny, w przeciwnym razie false.
    bool isSafe(int row, int col) const;

    // Funkcja sprawdzająca, czy pionek/damka znajduje się w centrum planszy.
    // Parametry:
    // - row, col: pozycja pionka/damki.
    // Zwraca true, jeśli pionek/damka jest w centrum planszy, w przeciwnym razie false.
    bool isCentral(int row, int col) const;

   public:
    // Konstruktor domyślny, który wywołuje metodę initializeBoard w celu ustawienia początkowego
    // stanu planszy.
    CheckersBoard();

    // Metoda do wyświetlenia aktualnego stanu planszy w terminalu.
    void printBoard();

    // Metoda do przemieszczania pionka na planszy.
    // Parametry:
    // - fromRow, fromCol: pozycja początkowa pionka
    // - toRow, toCol: pozycja końcowa pionka
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);

    // Metoda sprawdzająca poprawność ruchu.
    // Parametry:
    // - fromRow, fromCol: pozycja początkowa pionka
    // - toRow, toCol: pozycja końcowa pionka
    // - playerColor: kolor pionka
    // Zwraca true, jeśli ruch jest poprawny, w przeciwnym razie false.
    bool isCorrectMove(int fromRow, int fromCol, int toRow, int toCol, PieceColor playerColor);

    // Metoda zwracająca typ pionka na danym polu.
    // Parametry:
    // - row, col: pozycja pionka
    // Zwraca typ pionka na danym polu
    FieldType getFieldType(int row, int col) const;

    // Metoda zwracająca wszystkie możliwe ruchy dla danego koloru gracza.
    // Parametry:
    // - playerColor: kolor gracza, dla którego sprawdzane są możliwe ruchy.
    // Zwraca wektor wszystkich możliwych ruchów dla danego koloru gracza.
    std::vector<Move> getPossibleMoves(PieceColor playerColor);

    // Funkcja oceniająca stan planszy z perspektywy danego koloru gracza.
    // Parametry:
    // - playerColor: kolor gracza, dla którego oceniany jest stan planszy.
    // Zwraca ocenę stanu planszy jako liczbę całkowitą.
    int evaluateBoard(PieceColor playerColor) const; 

    // Metoda sprawdzająca, czy gra się zakończyła.
    // Zwraca true, jeśli gra się zakończyła, w przeciwnym razie false.
    bool isGameOver() const;
};
#endif