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

void CheckersBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (abs(rowDiff) == 2 && abs(colDiff) == 2 ) {
        // Bic
        int middleRow = (fromRow + toRow) / 2;
        int middleCol = (fromCol + toCol) / 2;
        board[middleRow][middleCol].clearSquare();
    }

    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol].clearSquare();
}


void CheckersBoard::clearSquare(int row, int col) {
    board[row][col].clearSquare();

}

void CheckersBoard::initializeBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Inicjalizacja czarnych pól
            if ((row < 3) && ((row + col) % 2 == 1)) {
                // Umieszczanie czarnych pionków w pierwszych trzech wierszach na czarnych polach
                board[row][col] = Piece(MAN, BLACK);
                // Inicjalizacja białych
            } else if ((row > 4) && ((row + col) % 2 == 1)) {
                // Umieszczanie białych pionków w ostatnich trzech wierszach na czarnych polach
                board[row][col] = Piece(MAN, WHITE);
            } else {
                // Pozostałe pola są puste
                board[row][col] = Piece();
            }
        }
    }
}
