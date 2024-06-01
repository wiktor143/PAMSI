#include "gameController.h"

gameController::gameController(CheckersBoard& b, Player& p1, Player& p2)
    : board(b), player1(p1), player2(p2), movesWithoutCapture(0), blackPieces(12), whitePieces(12) {
    // Rozpoczęcie gry
    status = RUNNING;
    // Oznacza pierwszy ruch
    firstRun = true;
    // Jeśli pierwszy jest czarny to pierwszy, jeśli nie to drugi zaczyna
    currentPlayer = (player1.getPlayerColor() == BLACK) ? &player1 : &player2;
}

void gameController::convertMove(int playerMove, int& row, int& col) {
    // Na początku zmiejszamy ruch o jedną wartość, ponieważ w tablicy iterujemy
    // od zera, następnie dzielimy przez 4, ponieważ są 4 pola(aktywne-czarne), w każdym wierszu.
    // Więc mamy liczby {1,2,3,4} - pierwszy wiersz, po odjęciu 1 i podzieleniu przez 4
    // dają wartość 0, czyli numer wiersza.
    // Analogicznie liczby {5,6,7,8} po odjęciu 1 i podzieleniu przez 4 dają 1(numer wiersza).
    row = (playerMove - 1) / 4;

    // Początek taki sam zmiejszamy o 1, żeby była możliwość dostać 0.
    // Następnie bierzemy resztę z dzielenia przez 4, to zapewnia nam idenks kolumny w obrębie
    // wiersza. Wartość 4, ponieważ mamy 4 aktywne pola. Mnożymy *2 bo w sumie w kolumnie jest 8
    // pól(4 aktywne i 4 nieaktywne, co drugie pole), czyli zakres od <0;6>. Ale brakuje nam kolumny
    // numer 7. Tym własnie zajmuje się działanie po znaku "+". Zapewnia odpowiednią kolumne dla
    // parzystych i nie parzystych numerów wierszy. Dla wierszy parzystych np. {0,2,...} numery
    // startują od kolumny = 0. Dla numerów nieparzystych wartości kolumn zaczynają się od numeru 1.
    // W skrócie przesunięcie o jeden w prawo.
    col = ((playerMove - 1) % 4) * 2 + ((row % 2 == 0) ? 1 : 0);
}

int gameController::convertToMoveIndex(int row, int col) const { return row * 4 + col / 2 + 1; }
bool gameController::parseMove(std::string& move, std::vector<int>& positions) {
    // Strumień o typie stringa, podobne do std::cin, ale
    // zamiast czytać ze standardowego wejścia czytamy ze stringa
    std::istringstream stringToRead(move);
    // Buffer na pozycje na planszy
    std::string positionBuffer;
    while (std::getline(stringToRead, positionBuffer, 'x')) {
        try {
            // Sprawdzenie, czy buffer zawiera tylko cyfry
            for (char c : positionBuffer) {
                if (!std::isdigit(c)) {
                    // Wyrzuć błąd
                    throw std::invalid_argument("Znaleziono inny znak nic cyfrę!");
                }
            }
            int position = std::stoi(positionBuffer);
            positions.push_back(position);
        } catch (...) {
            // W przypadku podania złego znaku zwróć false
            return false;
        }
    }
    return true;
}

void gameController::switchPlayer() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}
void gameController::updateGame() {}
void gameController::makeAiMove() {
    // Odebranie ruchu funkcji heurystycznej
    Move aiMove = currentPlayer->getAiMove();
    // Przypisanie ruchów pod odpwiednie indeksy
    int fromRow = aiMove.fromRow;
    int fromCol = aiMove.fromCol;
    int toRow = aiMove.toRow;
    int toCol = aiMove.toCol;
    // Zmienna potrzeba w przypadku promocji piona przy naliczaniu ilości ruchów bez
    // bicia;
    bool wantsPromotion = board.getFieldType(fromRow, fromCol) == MAN;
    // Ruch pionka, jeśli nie można zmienić pozycji pionka jest false
    if (!currentPlayer->makeMove(fromRow, fromCol, toRow, toCol)) {
        status = WRONG_MOVE;
    }
    std::cout << "ruch z :" << fromRow << ", " << fromCol << std::endl;
    std::cout << "ruch do :" << toRow << ", " << toCol << std::endl;
    std::cout << std::endl
              << "Komputer wykonał ruch z " << convertToMoveIndex(fromRow, fromCol) << " do "
              << convertToMoveIndex(toRow, toCol) << "." << std::endl
              << std::endl;

    // Akutalizacja ilości pionków na planszy
    bool isCapture = std::abs(toRow - fromRow) == 2;

    if (isCapture) {  // Jest bicie
        // Ustalenie jakiego koloru gracz teraz jest
        std::cout << "Zawodnik(komputer): "
                  << ((currentPlayer->getPlayerColor() == BLACK) ? "czarny" : "biały")
                  << " przeprowadził bicie" << std::endl;

        PieceColor opponentColor = (currentPlayer->getPlayerColor() == BLACK) ? WHITE : BLACK;
        if (opponentColor == WHITE) {  // Jeśli jest czarny
            whitePieces--;             // Zmniejszamy ilość jego pionków
        } else {
            blackPieces--;
        }
    }
    // Jeśli pojawiło się bicie lub ruszył się jakikolwiek pionek(bo muszą być
    // kolejne)
    if (isCapture || board.getFieldType(toRow, toCol) == MAN) {
        movesWithoutCapture = 0;  // Licznik na zero jeśli było bicie
        // Jeśli ruszyła się damka i nie było bicia oraz pionek dopiero nie wszedł
        // na pole promowane
    } else if (board.getFieldType(toRow, toCol) == KING && !wantsPromotion) {
        movesWithoutCapture++;  // Zwiększenie ilości ruchów bez bicia
        if (movesWithoutCapture == 20) {
            status = DRAFT;
        }
    }
    // Aktulizacja statusu gry, sprawdzenie czy ktoś wygrał po każdym ruchu
    isGameOver();
    // Aktualizacja gracza
}
gameStatus gameController::getGameStatus() const { return status; }

void gameController::isGameOver() {
    if (blackPieces == 0) {
        status = WIN_WHITE;
    }
    if (whitePieces == 0) {
        status = WIN_BLACK;
    }
}

void gameController::game() {
    std::cout << "Komputer gra kolorem: "
              << (player1.getPlayerColor() == BLACK ? "czarnym" : "białym") << std::endl;
    std::cout << "Człowiek gra kolorem: "
              << (player2.getPlayerColor() == BLACK ? "czarnym" : "białym") << std::endl;
    while (getGameStatus() == RUNNING) {
        if (currentPlayer->getPlayerType() == AI) {
            makeAiMove();
            switchPlayer();
        }

        // Plansza nie zostanie wyświetlona jeśli jest pierwszy ruch i wykonuje go AI i ai nie
        // zrobiło błedu
        if ((!firstRun || currentPlayer->getPlayerType() != AI) && getGameStatus() == RUNNING) {
            board.printBoard();
        }

        if (currentPlayer->getPlayerType() == HUMAN && getGameStatus() == RUNNING) {
            std::string move;
            std::vector<int> positions;
            std::cout << "Tura człowieka, ruch: "
                      << (currentPlayer->getPlayerColor() == BLACK ? "czarnych." : "białych.")
                      << std::endl;
            std::cout << "Na planszy jest: " << blackPieces << "-czarnych, " << whitePieces
                      << "-białych." << std::endl;
            std::cout << "Ilość ruchów samymi damkami: " << movesWithoutCapture << std::endl;
            std::cout << "Podaj ruch lub 'q' aby zakończyć: ";
            std::cin >> move;

            if (move == "q") {
                status = QUITED;
            }
            if (parseMove(move, positions) && getGameStatus() == RUNNING) {
                for (int i = 0; i < static_cast<int>(positions.size() - 1); ++i) {
                    int from = positions[i];
                    int to = positions[i + 1];
                    // Indeksy pozycji po konwersji z formatu np. 1x5
                    int fromRow, fromCol, toRow, toCol;
                    convertMove(from, fromRow, fromCol);
                    convertMove(to, toRow, toCol);
                    bool wantsPromotion = board.getFieldType(fromRow, fromCol) == MAN;
                    if (!currentPlayer->makeMove(fromRow, fromCol, toRow, toCol)) {
                        status = WRONG_MOVE;
                        break;
                    }
                    bool isCapture = std::abs(toRow - fromRow) == 2;
                    if (isCapture) {
                        std::cout << "Zawodnik(człowiek): "
                                  << ((currentPlayer->getPlayerColor() == BLACK) ? "czarny"
                                                                                 : "biały")
                                  << " przeprowadził bicie!" << std::endl;

                        PieceColor opponentColor =
                            (currentPlayer->getPlayerColor() == BLACK) ? WHITE : BLACK;
                        if (opponentColor == WHITE) {
                            whitePieces--;
                        } else {
                            blackPieces--;
                        }
                    }
                    if (isCapture || board.getFieldType(toRow, toCol) == MAN) {
                        movesWithoutCapture = 0;
                    } else if (board.getFieldType(toRow, toCol) == KING && !wantsPromotion) {
                        movesWithoutCapture++;
                        if (movesWithoutCapture == 20) {
                            status = DRAFT;
                        }
                    }
                }
                switchPlayer();
                isGameOver();
            } else {
                status = WRONG_MOVE;
            }
        }

        // Skończył się pierwszy ruch
        firstRun = false;

        // Warunki sprawdzające stan gry
        if (getGameStatus() == WRONG_MOVE) {
            std::cerr << "Error: Nieprawidłowy ruch!" << std::endl;
        } else if (getGameStatus() == QUITED) {
            std::cerr << "Zakończono grę!" << std::endl;
        } else if (getGameStatus() == DRAFT) {
            std::cerr << "Koniec gry: remis!" << std::endl;
        } else if (getGameStatus() == WIN_BLACK) {
            std::cerr << "Czarny wygrał!" << std::endl;
        } else if (getGameStatus() == WIN_WHITE) {
            std::cerr << "Biały wygrał!" << std::endl;
        }
    }
}