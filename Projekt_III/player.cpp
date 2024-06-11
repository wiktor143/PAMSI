#include "player.h"
// Konstruktor inicjalizujący gracza z podanym typem gracza, kolorem pionków i referencją do
// planszy.
Player::Player(playerType pT, PieceColor c, CheckersBoard& b) : whoIsPlaying(pT), playerColor(c), board(b) {}

// Metoda wykonująca ruch pionkiem na planszy.
// Sprawdza, czy ruch jest poprawny, a następnie przesuwa pionek.
bool Player::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (board.isCorrectMove(fromRow, fromCol, toRow, toCol, playerColor)) {
        board.movePiece(fromRow, fromCol, toRow, toCol);
        return true;
    }
    return false;
}

// Metoda zwracająca kolor pionków gracza.
PieceColor Player::getPlayerColor() const { return playerColor; }

// Metoda zwracająca typ gracza.
playerType Player::getPlayerType() const { return whoIsPlaying; }

// Metoda generująca ruch dla AI za pomocą algorytmu Minimax z odcięciami alfa-beta.
Move Player::getAiMove(int depth) {
    // Wektor przechowujący najlepsze ruchy
    std::vector<Move> bestMoves;

    // Inicjalizacja najlepszej wartości jako bardzo niska aby łatwo ją uaktualnić
    int bestValue = -10000;

    // Przejście przez wszystkie możliwe ruchy
    for (auto& move : board.getPossibleMoves(playerColor)) {
        // Kopia akutalnego stanu planszy
        CheckersBoard newBoard = board;

        // Symulacja ruchu
        newBoard.movePiece(move.fromRow, move.fromCol, move.toRow, move.toCol);

        // Wywołanie funkcji minimax z głębokością mniejszą o 1, dla przeciwnika (minimalizującego)
        int boardValue = miniMax(newBoard, depth - 1, -10000, 10000, false);

        // Sprawdzenie, czy wartość zwrócona przez minimax jest większa niż najlepsza znaleziona
        // dotychczas
        if (boardValue > bestValue) {
            bestValue = boardValue;     // Aktualizacja najlepszej wartości
            bestMoves.clear();          // Wyczyszczenie listy najlepszych ruchów
            bestMoves.push_back(move);  // Dodanie nowego najlepszego ruchu
        } else if (boardValue == bestValue) {
            // Dodanie ruchu o tej samej wartości co najlepszy dotychczasowy
            bestMoves.push_back(move);
        }
    }

    // Jeśli istnieją najlepsze ruchy, wybierz losowy ruch spośród najlepszych możliwych
    if (!bestMoves.empty()) {
        int randomIndex = rand() % bestMoves.size();  // Losowy indeks w zakresie 0 do bestMoves.size() - 1
        return bestMoves[randomIndex];
    }
    // Brak dostępnych ruchów, zwraca ruch, który nie jest poprawny
    return {-1, -1, -1, -1};
}

// Funkcja implementująca algorytm Minimax z odcięciami alfa-beta w celu oceny stanów gry.
int Player::miniMax(CheckersBoard board, int depth, int alpha, int beta, bool maximizingPlayer) {
    // Warunek zakończenia rekurencji: osiągnięcie maksymalnej głębokości lub koniec gry
    if (depth == 0 || board.isGameOver()) {
        return board.evaluateBoard(playerColor);  // Wywołanie funkcji oceniającej stan planszy
    }
    // Kolor gracza maksymalizującego i minimalizującego
    PieceColor maximizing = (getPlayerColor() == BLACK) ? BLACK : WHITE;
    PieceColor minimizing = (getPlayerColor() == BLACK) ? WHITE : BLACK;

    // Maksymalizujący gracz
    if (maximizingPlayer) {
        // Inicjalizacja maksymalnej wartości jako bardzo niskiej aby łatwo uaktualnić
        int maxEval = -10000;
        // Przejście przez wszystkie możliwe ruchy
        for (auto& move : board.getPossibleMoves(maximizing)) {
            CheckersBoard newBoard = board;  // Kopia aktualnej planszy
            newBoard.movePiece(move.fromRow, move.fromCol, move.toRow, move.toCol);  // Symulacja ruchu

            // Wywołanie funkcji minimax dla przeciwnika (minimalizującego gracza)
            int eval = miniMax(newBoard, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);  // Aktualizacja maksymalnej wartości
            alpha = std::max(alpha, eval);      // Aktualizacja alfa
            // Sprawdzenie warunku odcięcia beta
            if (beta < alpha) {
                break;  // Odcięcie beta
            }
        }
        return maxEval;  // Zwrócenie maksymalnej wartości
    } else {
        // Minimalizujący gracz (przeciwnik)
        int minEval = 10000;  // Inicjalizacja minimalnej wartości jako bardzo wysokiej aby łatwo ją uaktualnić
        for (auto& move : board.getPossibleMoves(minimizing)) {
            CheckersBoard newBoard = board;  // Kopia aktualnej planszy
            newBoard.movePiece(move.fromRow, move.fromCol, move.toRow, move.toCol);  // Symulacja ruchu

            // Wywołanie funkcji minimax dla gracza maksymalizującego (AI)
            int eval = miniMax(newBoard, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);  // Aktualizacja minimalnej wartości
            beta = std::min(beta, eval);        // Aktualizacja beta
            // Sprawdzenie warunku odcięcia alfa
            if (beta < alpha) {
                break;  // Odcięcie alfa
            }
        }

        return minEval; // Zwrócenie minimalnej wartości
    }
}
