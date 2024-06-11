#include "checkersBoard.h"

// Konstruktor klasy CheckersBoard, inicjalizuje planszę do gry.
CheckersBoard::CheckersBoard() { 
    initializeBoard();
}

// Metoda do wyświetlania aktualnego stanu planszy w terminalu.
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

// Metoda do przemieszczania pionka na planszy.
void CheckersBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    // Bicie (ruch o dwa pola)
    if (abs(rowDiff) == 2 && abs(colDiff) == 2) {
        int middleRow = (fromRow + toRow) / 2;
        int middleCol = (fromCol + toCol) / 2;
        board[middleRow][middleCol].clearSquare();  // Usunięcie zbitego pionka
    }

    // Przeniesienie pionka na nowe miejsce
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

// Metoda inicjalizująca planszę do gry.
void CheckersBoard::initializeBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Inicjalizacja czarnych pól
            if ((row < 3) && ((row + col) % 2 == 1)) {
                board[row][col] = Field(MAN, BLACK);  // Umieszczanie czarnych pionków
                // Inicjalizacja białych
            } else if ((row > 4) && ((row + col) % 2 == 1)) {
                board[row][col] = Field(MAN, WHITE);  // Umieszczanie białych pionków
            } else {
                board[row][col] = Field();  // Pozostałe pola są puste
            }
        }
    }
}

// Metoda sprawdzająca poprawność ruchu.
bool CheckersBoard::isCorrectMove(int fromRow, int fromCol, int toRow, int toCol, PieceColor playerColor) {
    // Dolna i górna granica wierszy pozycji początkowej
    if (fromRow < 0 || fromRow > 7) {
        return false;
    }
    // Dolna i górna granica kolumn pozycji początkowej
    if (fromCol < 0 || fromCol > 7) {
        return false;
    }
    // Dolna i górna granica wierszy pozycji docelowej
    if (toRow < 0 || toRow > 7) {
        return false;
    }

    // Dolna i górna granica kolumn pozycji docelowej
    if (toCol < 0 || toCol > 7) {
        return false;
    }
    // Sprawdzenie, czy na pozycji wyjściowej jest pionek
    if (board[fromRow][fromCol].getType() == NONE) {
        return false;
    }

    // Sprawdzenie, czy na pozycji docelowej jest pionek
    if (board[toRow][toCol].getType() != NONE) {
        return false;
    }
    // Sprawdzenie, czy gracz nie próbuje ruszać pionków przeciwnika
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
        }  // Biały może wykonać ruch o jeden w doł oraz jeden w lewo i w prawo
        else if (board[fromRow][fromCol].getColor() == WHITE && rowDiff == -1 && abs(colDiff) == 1) {
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
                return false;
            }
            // Sprawdzenie logiki bicia dla pionka białego
        } else if (board[fromRow][fromCol].getColor() == WHITE && rowDiff == -2 && abs(colDiff) == 2) {
            int middleRow = (fromRow + toRow) / 2;
            int middleCol = (fromCol + toCol) / 2;
            // Jeśli na polu środkowym znajduje się przeciwnik
            if (board[middleRow][middleCol].getColor() != NO_COLOR &&
                board[middleRow][middleCol].getColor() != board[fromRow][fromCol].getColor()) {
                return true;
            } else {
                return false;
            }
        }
        // W przeciwnym razie jak zadany został zły ruch
        else {
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
                return false;
            }
        } else {
            return false;
        }
    }
    return false;
}

// Metoda zwracająca typ pola na danej pozycji.
FieldType CheckersBoard::getFieldType(int row, int col) const { 
    return board[row][col].getType(); 
}

// Metoda zwracająca możliwe ruchy dla danego gracza.
std::vector<Move> CheckersBoard::getPossibleMoves(PieceColor playerColor) {
    std::vector<Move> moves;
    std::vector<Move> captureMoves;

    // Iteracja po wszystkich wierszach
    for (int row = 0; row < 8; ++row) {
        // Iteracja po wszystkich kolumnach
        for (int col = 0; col < 8; ++col) {
            // Sprawdzenie, czy na danym polu znajduje się pionek koloru gracza
            if (board[row][col].getColor() == playerColor) {
                // Znalezienie możliwych ruchów bicia dla pionka/damki
                findCaptureMoves(captureMoves, row, col, playerColor);
                // Jeśli nie ma możliwych ruchów bicia, znalezienie normalnych ruchó
                if (captureMoves.empty()) {
                    findNormalMoves(moves, row, col, playerColor);
                }
            }
        }
    }
    // Zwrócenie ruchów bicia, jeśli są dostępne, w przeciwnym razie normalnych ruchów
    return !captureMoves.empty() ? captureMoves : moves;
}

// Metoda znajdująca możliwe ruchy bicia dla pionka
void CheckersBoard::findCaptureMoves(std::vector<Move>& captureMoves, int row, int col, PieceColor playerColor) {
    // Tablice definiujące przesunięcia dla ruchu bicia (o dwa pola)
    int dRowCapture[] = {-2, -2, 2, 2};
    int dColCapture[] = {-2, 2, -2, 2};

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dRowCapture[i];
        int newCol = col + dColCapture[i];
        // Sprawdzenie, czy ruch bicia jest poprawny
        if (isCorrectMove(row, col, newRow, newCol, playerColor)) {
            Move move = {row, col, newRow, newCol};
            CheckersBoard tempBoard = *this;
            int capturedRow = (row + newRow) / 2;
            int capturedCol = (col + newCol) / 2;
            // Aktualizacja tymczasowej planszy
            tempBoard.board[capturedRow][capturedCol].clearSquare();  // Usuń zbitego pionka
            tempBoard.board[newRow][newCol] = board[row][col];  // Przenieś pionek na nowe miejsce
            tempBoard.board[row][col].clearSquare();            // Usuń pionek ze starego miejsca

            // Rekurencyjne znajdowanie kolejnych ruchów bicia
            tempBoard.recursiveCaptureMoves(move, newRow, newCol, playerColor);
            captureMoves.push_back(move);
        }
    }
}

// Metoda znajdująca możliwe normalne ruchy dla pionka
void CheckersBoard::findNormalMoves(std::vector<Move>& moves, int row, int col, PieceColor playerColor) {
    // Tablice definiujące przesunięcia dla ruchu na ukos o jedno pole (normalny ruch)
    int dRow[] = {-1, -1, 1, 1};
    int dCol[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dRow[i];
        int newCol = col + dCol[i];
        // Sprawdzenie, czy normalny ruch jest poprawny
        if (isCorrectMove(row, col, newRow, newCol, playerColor)) {
            moves.push_back({row, col, newRow, newCol});
        }
    }
}

// Rekurencyjna metoda znajdująca kolejne ruchy bicia dla pionka
void CheckersBoard::recursiveCaptureMoves(Move& move, int row, int col, PieceColor playerColor) {
    // Tablice definiujące przesunięcia dla ruchu bicia (o dwa pola)
    int dRowCapture[] = {-2, -2, 2, 2};
    int dColCapture[] = {-2, 2, -2, 2};
    bool captureFound = false;

    for (int i = 0; i < 4; ++i) {
        int newRow = row + dRowCapture[i];
        int newCol = col + dColCapture[i];
        // Sprawdzenie, czy ruch bicia jest poprawny
        if (isCorrectMove(row, col, newRow, newCol, playerColor)) {
            Move nextMove = {row, col, newRow, newCol};
            CheckersBoard tempBoard = *this;
            int capturedRow = (row + newRow) / 2;
            int capturedCol = (col + newCol) / 2;
            // Aktualizacja tymczasowej planszy
            tempBoard.board[capturedRow][capturedCol].clearSquare();  // Usuń zbitego pionka
            tempBoard.board[newRow][newCol] = board[row][col];  // Przenieś pionek na nowe miejsce
            tempBoard.board[row][col].clearSquare();            // Usuń pionek ze starego miejsca

            // Rekurencyjne znajdowanie kolejnych ruchów bicia
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
            Field piece = board[i][j];
            if (piece.getColor() != NO_COLOR) {
                int pieceValue = 0;

                // Ustalanie podstawowej wartości na podstawie typu pionka
                if (piece.getType() == MAN) {
                    pieceValue = 1;

                    // Dodatkowa wartość dla pionków w zależności od odległości do linii promocji
                    // Zachęca pionki do poruszania się w kierunku awansu
                    if (piece.getColor() == BLACK) {
                        pieceValue += (7 - i);  // Odległość do promocji dla czarnych
                    } else {
                        pieceValue += i;  // Odległość do promocji dla białych
                    }

                    // Bonus za bezpieczną pozycję (przy krawędzi planszy)
                    if (isSafe(i, j)) {
                        pieceValue += 1;
                    }

                    // Bonus za kontrolę centrum planszy
                    if (isCentral(i, j)) {
                        pieceValue += 1;
                    }
                } else if (piece.getType() == KING) {
                    pieceValue = 3;

                    // Bonus za bezpieczną pozycję króla
                    if (isSafe(i, j)) {
                        pieceValue += 1;
                    }

                    // Bonus za kontrolę centrum planszy przez króla
                    if (isCentral(i, j)) {
                        pieceValue += 1;
                    }
                }

                // Dodawanie punktów do wyniku gracza lub przeciwnika na podstawie koloru pionka
                if (piece.getColor() == playerColor) {
                    score += pieceValue;
                } else {
                    score -= pieceValue;
                }
            }
        }
    }

    return score;
}

// Funkcja sprawdzająca, czy pionek jest bezpieczny (przy krawędzi planszy)
bool CheckersBoard::isSafe(int row, int col) const {
    return (row == 0 || row == 7 || col == 0 || col == 7);
}

// Funkcja sprawdzająca, czy pionek/król znajduje się w centrum planszy
bool CheckersBoard::isCentral(int row, int col) const {
    return (row > 2 && row < 5 && col > 2 && col < 5);
}

// Funkcja sprawdzająca, czy gra jest zakończona
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
    // Gra kończy się, gdy jeden z graczy nie ma pionków
    return blackPieces == 0 || whitePieces == 0;
}
