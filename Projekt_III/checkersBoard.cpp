#include "checkersBoard.h"
CheckersBoard::CheckersBoard() { initializeBoard(); }
void CheckersBoard::printBoard() {
    std::cout << "    1   2   3   4   5   6   7   8" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        std::cout << i + 1 << " |";
        for (int j = 0; j < 8; ++j) {
            // Jeśli mamy pionka 
            if (board[i][j].getColor() != NO_COLOR) {
                std::cout << " " << board[i][j].getSymbol() << " |";
            } else {
                std::cout << "   |";
            }
        }
        std::cout << " " << i + 1 << std::endl;
    }
    std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;

}

void CheckersBoard::initializeBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Inicjalizacja czarnych pól 
            if ((row < 3) && ((row + col) % 2 == 1)) {
                // Umieszczanie czarnych pionków w pierwszych trzech wierszach na czarnych polach
                board[row][col] = Piece(MAN, BLACK, ACTIVE);
                // Inicjalizacja białych pól
            } else if ((row > 4) &&((row + col) % 2 == 1)) {
                // Umieszczanie białych pionków w ostatnich trzech wierszach na czarnych polach
                board[row][col] = Piece(MAN, WHITE, ACTIVE);
            } else {
                // Pozostałe pola są puste
                board[row][col] = Piece();
            }
        }
    }
}
