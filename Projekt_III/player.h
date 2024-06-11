#ifndef PLAYER_H
#define PLAYER_H
#include <chrono>

#include "checkersBoard.h"

// Enum definiujący typy graczy: człowiek (HUMAN) i AI (AI).
enum playerType { HUMAN, AI };

class Player {
   private:
    // Metoda implementująca algorytm Minimax z odcięciami alfa-beta w celu oceny stanów gry.
    // Parametry:
    // - board: kopia aktualnej planszy
    // - depth: głębokość przeszukiwania drzewa stanów
    // - alpha: wartość alfa dla odcięć alfa-beta
    // - beta: wartość beta dla odcięć alfa-beta
    // - maximizingPlayer: flaga wskazująca, czy obecny ruch jest maksymalizujący czy minimalizujący
    // Zwraca wartość oceny planszy dla najlepszego możliwego ruchu.
    int miniMax(CheckersBoard board, int depth, int alpha, int beta, bool maximizingPlayer);

    playerType whoIsPlaying;  // Typ gracza (HUMAN lub AI).
    PieceColor playerColor;   // Kolor pionków gracza (BLACK lub WHITE).
    CheckersBoard& board;     // Referencja do obiektu CheckersBoard reprezentującego planszę.
    
   public:
    // Konstruktor inicjalizujący gracza z podanym typem gracza, kolorem pionków i referencją do
    // planszy. Parametry:
    // - playerType: typ gracza (HUMAN lub AI)
    // - color: kolor pionków gracza (BLACK lub WHITE)
    // - board: referencja do obiektu CheckersBoard reprezentującego planszę
    Player(playerType playerType, PieceColor color, CheckersBoard& board);

    // Metoda wykonująca ruch pionkiem na planszy.
    // Parametry:
    // - fromRow, fromCol: współrzędne początkowe pionka
    // - toRow, toCol: współrzędne docelowe pionka
    // Zwraca true, jeśli ruch był prawidłowy, w przeciwnym razie false.
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);

    // Metoda generująca ruch dla AI za pomocą algorytmu Minimax z odcięciami alfa-beta.
    // Parametry:
    // - depth: głębokość przeszukiwania drzewa stanów
    // Zwraca obiekt Move reprezentujący najlepszy ruch wygenerowany przez AI.
    Move getAiMove(int depth);

    // Metoda zwracająca kolor pionków gracza.
    // Zwraca wartość typu PieceColor (BLACK lub WHITE).
    PieceColor getPlayerColor() const;

    // Metoda zwracająca typ gracza.
    // Zwraca wartość typu playerType (HUMAN lub AI).
    playerType getPlayerType() const;
};

#endif