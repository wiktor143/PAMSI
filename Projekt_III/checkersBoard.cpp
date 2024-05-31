#include "checkersBoard.h"
CheckersBoard::CheckersBoard() { initializeBoard(); }
void CheckersBoard::printBoard() {
    int fieldNumber = 1;
    std::cout<<"#=====================================#"<<std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        std::cout << i + 1 << " |";
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 1) {
                if (board[i][j].getColor() != NO_COLOR && fieldNumber < 10) {
                    std::cout << board[i][j].getSymbol() << fieldNumber << " |";
                } else if ((board[i][j].getColor() != NO_COLOR && fieldNumber >= 10)) {
                    std::cout << board[i][j].getSymbol() << fieldNumber << "|";
                } else if (fieldNumber < 10) {
                    std::cout << fieldNumber << "  |";
                } else {
                    std::cout << fieldNumber << " |";
                }

                fieldNumber++;
            } else {
                std::cout << "   |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
}

void CheckersBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    // Bicie
    if (abs(rowDiff) == 2 && abs(colDiff) == 2) {
        int middleRow = (fromRow + toRow) / 2;
        int middleCol = (fromCol + toCol) / 2;
        board[middleRow][middleCol].clearSquare();
    }

    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol].clearSquare();

    // Promocja pionka na damkę
    if (board[toRow][toCol].getType() == MAN) {
        if ((board[toRow][toCol].getColor() == BLACK && toRow == 7) ||
            (board[toRow][toCol].getColor() == WHITE && toRow == 0)) {
            board[toRow][toCol].promotePiece();
        }
    }
}

void CheckersBoard::initializeBoard() {
    // for (int row = 0; row < 8; ++row) {
    //     for (int col = 0; col < 8; ++col) {
    //         // Inicjalizacja czarnych pól
    //         if ((row < 3) && ((row + col) % 2 == 1)) {
    //             // Umieszczanie czarnych pionków w pierwszych trzech wierszach na czarnych polach
    //             board[row][col] = Field(MAN, BLACK);
    //             // Inicjalizacja białych
    //         } else if ((row > 4) && ((row + col) % 2 == 1)) {
    //             // Umieszczanie białych pionków w ostatnich trzech wierszach na czarnych polach
    //             board[row][col] = Field(MAN, WHITE);
    //         } else {
    //             // Pozostałe pola są puste
    //             board[row][col] = Field();
    //         }
    //     }
    // }
    board[6][1] = Field(MAN, BLACK);
    board[1][2] = Field(MAN, WHITE);
}

bool CheckersBoard::isCorrectMove(int fromRow, int fromCol, int toRow, int toCol,
                                  PieceColor playerColor) {
    // Dolna i górna granica wierszy pozycji początkowej
    if (fromRow < 0 || fromRow > 7) {
        std::cerr << "Error: Zła pozycja wyjściowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }
    // Dolna i górna granica kolumn pozycji początkowej
    if (fromCol < 0 || fromCol > 7) {
        std::cerr << "Error: Zła pozycja wyjściowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }
    // Dolna i górna granica wierszy pozycji docelowej
    if (toRow < 0 || toRow > 7) {
        std::cerr << "Error: Zła pozycja docelowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }

    // Dolna i górna granica kolumn pozycji docelowej
    if (toCol < 0 || toCol > 7) {
        std::cerr << "Error: Zła pozycja docelowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }
    // Sprawdzenie, czy na pozycji wyjściowej jest pionek
    if (board[fromRow][fromCol].getType() == NONE) {
        std::cerr << "Error: Ruch z pozycji pustej!" << std::endl;
        return false;
    }
    // Sprawdzenie, czy na docelowej pozycji znajduje się już pionek.
    // Jeśli tak zwraca false
    if (board[toRow][toCol].getType() != NONE) {
        std::cerr << "Error: Ruch na pozycję już zajętą!" << std::endl;
        return false;
    }

    if (board[fromRow][fromCol].getColor() != playerColor) {
        std::cerr << "Error: Nie można ruszać pionków przeciwnika!" << std::endl;
        return false;
    }
    // Obliczenie różnicy wierszy
    int rowDiff = toRow - fromRow;

    // Obliczenie różnicy kolumn
    int colDiff = toCol - fromCol;

    // Sprawdzenie logiki ruchu zwykłego pionka
    if (board[fromRow][fromCol].getType() == MAN) {
        // Czarny może wykonać ruch o jeden w doł oraz jeden w lewo i w prawo
        if (board[fromRow][fromCol].getColor() == BLACK && rowDiff == 1 && abs(colDiff) == 1) {
            return true;
        }  // Biały może wykonać ruch  o jeden w doł oraz jeden w lewo i w prawo
        else if (board[fromRow][fromCol].getColor() == WHITE && rowDiff == -1 &&
                 abs(colDiff) == 1) {
            return true;
        }
        // Sprawdzenie logiki bicia
        else if (abs(rowDiff) == 2 && abs(colDiff) == 2) {
            int middleRow = (fromRow + toRow) / 2;
            int middleCol = (fromCol + toCol) / 2;
            // Jeśli na polu środkowym znajduje się przeciwnik
            if (board[middleRow][middleCol].getColor() != NO_COLOR &&
                board[middleRow][middleCol].getColor() != board[fromRow][fromCol].getColor()) {
                return true;
            } else {
                std::cerr << "Error: Nieprawidłowy ruch bicia!" << std::endl;
                return false;
            }
        }  // W przeciwnym razie jak zadany został zły ruch
        else {
            std::cerr << "Error: Nieprawidłowy ruch pionka!" << std::endl;
            return false;
        }
    }

    // Sprawdzenie logiki ruchu damki (KING)
    if (board[fromRow][fromCol].getType() == KING) {
        // Damka może się poruszać o jeden w dowolnym kierunku
        if (abs(rowDiff) == 1 && abs(colDiff) == 1) {
            return true;
        }
        // Sprawdzenie logiki bicia damką
        else if (abs(rowDiff) == 2 && abs(colDiff) == 2) {
            int middleRow = (fromRow + toRow) / 2;
            int middleCol = (fromCol + toCol) / 2;
            if (board[middleRow][middleCol].getColor() != NO_COLOR &&
                board[middleRow][middleCol].getColor() != board[fromRow][fromCol].getColor()) {
                return true;
            } else {
                std::cerr << "Error: Nieprawidłowy ruch bicia damki!" << std::endl;
                return false;
            }
        } else {
            std::cerr << "Error: Nieprawidłowy ruch damki!" << std::endl;
            return false;
        }
    }
    return true;
}

FieldType CheckersBoard::getFieldType(int row, int col) const { return board[row][col].getType(); }
