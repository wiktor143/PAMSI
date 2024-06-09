#include "checkersBoard.h"
CheckersBoard::CheckersBoard() { initializeBoard(); }
void CheckersBoard::printBoard() {
    int fieldNumber = 1;
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
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Inicjalizacja czarnych pól
            if ((row < 3) && ((row + col) % 2 == 1)) {
                // Umieszczanie czarnych pionków w pierwszych trzech wierszach na czarnych polach
                board[row][col] = Field(MAN, BLACK);
                // Inicjalizacja białych
            } else if ((row > 4) && ((row + col) % 2 == 1)) {
                // Umieszczanie białych pionków w ostatnich trzech wierszach na czarnych polach
                board[row][col] = Field(MAN, WHITE);
            } else {
                // Pozostałe pola są puste
                board[row][col] = Field();
            }
        }
    }
    // board[1][2] = Field(MAN, BLACK);
    // // board[1][0] = Field(MAN, WHITE);
    // board[2][3] = Field(MAN, WHITE);
    // board[4][5] = Field(MAN, WHITE);

    // // board[2][3] = Field(MAN, WHITE);

    // // board[6][5] = Field(MAN, WHITE);
}

bool CheckersBoard::isCorrectMove(int fromRow, int fromCol, int toRow, int toCol,
                                  PieceColor playerColor) {
    // Dolna i górna granica wierszy pozycji początkowej
    if (fromRow < 0 || fromRow > 7) {
        // std::cerr << "Error: Zła pozycja wyjściowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }
    // Dolna i górna granica kolumn pozycji początkowej
    if (fromCol < 0 || fromCol > 7) {
        // std::cerr << "Error: Zła pozycja wyjściowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }
    // Dolna i górna granica wierszy pozycji docelowej
    if (toRow < 0 || toRow > 7) {
        // std::cerr << "Error: Zła pozycja docelowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }

    // Dolna i górna granica kolumn pozycji docelowej
    if (toCol < 0 || toCol > 7) {
        // std::cerr << "Error: Zła pozycja docelowa. Numeracja pozycji od 1 do 32." << std::endl;
        return false;
    }
    // Sprawdzenie, czy na pozycji wyjściowej jest pionek
    if (board[fromRow][fromCol].getType() == NONE) {
        // std::cerr << "Error: Ruch z pozycji pustej!" << std::endl;
        return false;
    }
    // Sprawdzenie, czy na docelowej pozycji znajduje się już pionek.
    // Jeśli tak zwraca false
    if (board[toRow][toCol].getType() != NONE) {
        // std::cerr << "Error: Ruch na pozycję już zajętą!" << std::endl;
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
        // Sprawdzenie logiki bicia dla pionka czarnego
        else if (board[fromRow][fromCol].getColor() == BLACK && rowDiff == 2 && abs(colDiff) == 2) {
            int middleRow = (fromRow + toRow) / 2;
            int middleCol = (fromCol + toCol) / 2;
            // Jeśli na polu środkowym znajduje się przeciwnik i nie pole nie jest puste(brak
            // pionka)
            if (board[middleRow][middleCol].getColor() != NO_COLOR &&
                board[middleRow][middleCol].getColor() != board[fromRow][fromCol].getColor()) {
                return true;
            } else {
                // std::cerr << "Error: Nieprawidłowy ruch bicia!" << std::endl;
                return false;
            }
            // Sprawdzenie logiki bicia dla pionka białego
        } else if (board[fromRow][fromCol].getColor() == WHITE && rowDiff == -2 &&
                   abs(colDiff) == 2) {
            int middleRow = (fromRow + toRow) / 2;
            int middleCol = (fromCol + toCol) / 2;
            // Jeśli na polu środkowym znajduje się przeciwnik
            if (board[middleRow][middleCol].getColor() != NO_COLOR &&
                board[middleRow][middleCol].getColor() != board[fromRow][fromCol].getColor()) {
                return true;
            } else {
                // std::cerr << "Error: Nieprawidłowy ruch bicia!" << std::endl;
                return false;
            }
        }
        // W przeciwnym razie jak zadany został zły ruch
        else {
            // std::cerr << "Error: Nieprawidłowy ruch pionka!" << std::endl;
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
                // std::cerr << "Error: Nieprawidłowy ruch bicia damki!" << std::endl;
                return false;
            }
        } else {
            // std::cerr << "Error: Nieprawidłowy ruch damki!" << std::endl;
            return false;
        }
    }
    return false;
}

FieldType CheckersBoard::getFieldType(int row, int col) const { return board[row][col].getType(); }

std::vector<Move> CheckersBoard::getPossibleMoves(PieceColor playerColor) {
    std::vector<Move> moves;
    std::vector<Move> captureMoves;

    // Iteracja po wszystkich wierszach
    for (int row = 0; row < 8; ++row) {
        // Iteracja po wszystkich kolumnach
        for (int col = 0; col < 8; ++col) {
            // Sprawdzenie, czy na danym polu znajduje się pionek koloru gracza
            if (board[row][col].getColor() == playerColor) {
                findCaptureMoves(captureMoves, row, col, playerColor);
                // Sprawdzenie wszystkich możliwych przesunięć o jedno pole na ukos (normalny ruch)
                if (captureMoves.empty()) {
                    findNormalMoves(moves, row, col, playerColor);
                }
            }
        }
    }
    return !captureMoves.empty() ? captureMoves : moves;
}

void CheckersBoard::findCaptureMoves(std::vector<Move>& captureMoves, int row, int col,
                                     PieceColor playerColor) {
    int dRowCapture[] = {-2, -2, 2, 2};
    int dColCapture[] = {-2, 2, -2, 2};

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dRowCapture[i];
        int newCol = col + dColCapture[i];
        if (isCorrectMove(row, col, newRow, newCol, playerColor)) {
            Move move = {row, col, newRow, newCol};
            CheckersBoard tempBoard = *this;
            int capturedRow = (row + newRow) / 2;
            int capturedCol = (col + newCol) / 2;
            // Aktualizacja tymczasowej planszy
            tempBoard.board[capturedRow][capturedCol].clearSquare();  // Usuń zbitego pionka
            tempBoard.board[newRow][newCol] = board[row][col];  // Przenieś pionek na nowe miejsce
            tempBoard.board[row][col].clearSquare();            // Usuń pionek ze starego miejsca

            tempBoard.recursiveCaptureMoves(move, newRow, newCol, playerColor);
            captureMoves.push_back(move);
        }
    }
}

void CheckersBoard::findNormalMoves(std::vector<Move>& moves, int row, int col,
                                    PieceColor playerColor) {
    // Tablice definiujące przesunięcia dla ruchu na ukos o jedno pole (normalny ruch)
    int dRow[] = {-1, -1, 1, 1};
    int dCol[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dRow[i];
        int newCol = col + dCol[i];
        if (isCorrectMove(row, col, newRow, newCol, playerColor)) {
            moves.push_back({row, col, newRow, newCol});
        }
    }
}

void CheckersBoard::recursiveCaptureMoves(Move& move, int row, int col, PieceColor playerColor) {
    int dRowCapture[] = {-2, -2, 2, 2};
    int dColCapture[] = {-2, 2, -2, 2};
    bool captureFound = false;

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dRowCapture[i];
        int newCol = col + dColCapture[i];
        if (isCorrectMove(row, col, newRow, newCol, playerColor)) {
            Move nextMove = {row, col, newRow, newCol};
            CheckersBoard tempBoard = *this;
            int capturedRow = (row + newRow) / 2;
            int capturedCol = (col + newCol) / 2;
            // Aktualizacja tymczasowej planszy
            tempBoard.board[capturedRow][capturedCol].clearSquare();  // Usuń zbitego pionka
            tempBoard.board[newRow][newCol] = board[row][col];  // Przenieś pionek na nowe miejsce
            tempBoard.board[row][col].clearSquare();            // Usuń pionek ze starego miejsca

            tempBoard.recursiveCaptureMoves(nextMove, newRow, newCol, playerColor);
            move.nextCaptures.push_back(nextMove);
            captureFound = true;
        }
    }

    if (!captureFound) {
        return;
    }
}

int CheckersBoard::evaluateBoard(PieceColor playerColor) const {
    int score = 0;
    // Przeliczanie punktów dla każdego pola
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j].getType() == MAN) {
                if (board[i][j].getColor() == playerColor) {
                    score += 1;  // Dodatnie punkty dla bieżącego gracza
                } else if (board[i][j].getColor() != NO_COLOR) {
                    score -= 1;  // Ujemne punkty dla przeciwnika
                }
            } else if (board[i][j].getType() == KING) {
                if (board[i][j].getColor() == playerColor) {
                    score += 2;  // Dodatnie punkty dla bieżącego gracza
                } else if (board[i][j].getColor() != NO_COLOR) {
                    score -= 2;  // Ujemne punkty dla przeciwnika
                }
            }
        }
    }
    return score;
    
}


bool CheckersBoard::isGameOver() const {
    int blackPieces = 0;
    int whitePieces = 0;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].getColor() == BLACK) {
                blackPieces++;
            } else if (board[row][col].getColor() == WHITE) {
                whitePieces++;
            }
        }
    }

    return blackPieces == 0 || whitePieces == 0;
}
