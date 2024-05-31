#include "gameController.h"

gameController::gameController(CheckersBoard& b, Player& p1, Player& p2)
    : board(b), player1(p1), player2(p2), movesWithoutCapture(0) {
    // Rozpoczęcie gry
    status = RUNNING;
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
gameStatus gameController::getGameStatus() const { return status; }

void gameController::game() {
    while (getGameStatus() == RUNNING) {
        board.printBoard();
        std::cout << "Tura gracza: "
                  << (currentPlayer->getPlayerColor() == BLACK ? "czarnego" : "białego")
                  << std::endl;
        std::cout << "Podaj ruch lub 'q' aby zakończyć: ";
        std::string move;
        std::vector<int> positions;
        std::cin >> move;
        std::cout << std::endl;

        if (move == "q") {
            status = QUITED;
        }

        // running bo może być już quit
        if (parseMove(move, positions) && getGameStatus() == RUNNING) {
            // Pętla w przypadku, kiedy mamy przesinięcie pionka o więcej niż jedno pole np.12x16x19
            for (int i = 0; i < static_cast<int>(positions.size() - 1); ++i) {
                // Pozycja początkowa
                int from = positions[i];
                // Pozycja docelowa
                int to = positions[i + 1];
                // Indeksy pozycji po konwersji z formatu np. 1x5
                int fromRow, fromCol, toRow, toCol;

                // Konwersja koordynatupoczątkowego na indeksy tablicy
                convertMove(from, fromRow, fromCol);
                // Konwersja koordynatu docelowego na indeksy tablicy
                convertMove(to, toRow, toCol);

                bool isCapture = std::abs(toRow - fromRow) == 2;

                // Zmienna potrzeba w przypadku promocji piona przy naliczaniu ilości ruchów bez
                // bicia;
                bool wantsPromotion = board.getFieldType(fromRow, fromCol) == MAN;
                // Przesunięcie pionka, jeśli nie można przesunąc jest false
                if (!currentPlayer->makeMove(fromRow, fromCol, toRow, toCol)) {
                    status = WRONG_MOVE;
                    break;
                }
                // Jeśli pojawiło się bicie lub ruszył się jakikolwiek pionek(bo muszą być kolejne)
                if (isCapture || board.getFieldType(toRow, toCol) == MAN) {
                    movesWithoutCapture = 0;  // Licznik na zero jeśli było bicie
                    // Jeśli ruszyła się damka i nie było bicia oraz pionek dopiero nie wszedł na
                    // pole promowane
                } else if (board.getFieldType(toRow, toCol) == KING && !wantsPromotion) {
                    movesWithoutCapture++;  // Zwiększenie ilości ruchów bez bicia
                    if (movesWithoutCapture == 20) {
                        status = DRAFT;
                    }
                }
            }
            // Aktualizacja gracza
            switchPlayer();
            // Jeśli użytkownik podał zły format ruchu np. 2s3
        } else {
            status = WRONG_MOVE;
        }

        // Warunki sprawdzające stan gry
        if (getGameStatus() == WRONG_MOVE) {
            std::cerr << "Error: Nieprawidłowy format ruchu!" << std::endl;
        } else if (getGameStatus() == QUITED) {
            std::cerr << "Zakończono gre!" << std::endl;
        } else if (getGameStatus() == DRAFT) {
            std::cerr << "Koniec gry: remis!" << std::endl;
        }
    }
}
