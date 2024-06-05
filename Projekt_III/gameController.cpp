#include "gameController.h"

gameController::gameController(CheckersBoard& b, Player& p1, Player& p2)
    : board(b), player1(p1), player2(p2), movesWithoutCapture(0), blackPieces(12), whitePieces(12) {
    // Rozpoczęcie gry
    status = RUNNING;

    serv_sock = -1;
    // Oznacza pierwszy ruch
    firstRun = true;
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

    char delimiter = move.find('x') != std::string::npos ? 'x' : '-';
    while (std::getline(stringToRead, positionBuffer, delimiter)) {
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

    // Dodatkowe sprawdzenie czy ruch jest poprawnie wykonany
    for (int i = 0; i < static_cast<int>(positions.size()) - 1; ++i) {
        int prev = positions[i];
        int curr = positions[i + 1];
        int diff = std::abs(prev - curr);
        // Jeśli jest zwykłe przsunięcie i rozmiar nie wynosi 2 lub przesunięcie jest więcej niż o
        // 4,5 lub 3 zwróć false
        if (delimiter == '-' &&
            (static_cast<int>(positions.size() != 2 || (diff != 4 && diff != 5 && diff != 3)))) {
            return false;
        }
        // Dla bicia różnica wynosi 7 lub 9
        if (delimiter == 'x' && (diff != 7 && diff != 9)) {
            return false;
        }
    }
    return true;
}

void gameController::switchPlayer() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}
void gameController::updateGameStatus() {
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
    std::cout << "Komputer wykonał ruch z " << convertToMoveIndex(fromRow, fromCol) << " do "
              << convertToMoveIndex(toRow, toCol) << std::endl
              << std::endl;

    // Akutalizacja ilości pionków na planszy
    bool isCapture = std::abs(toRow - fromRow) == 2;

    if (isCapture) {  // Jest bicie
        // Ustalenie jakiego koloru gracz teraz jest
        std::cout << "Komputer: "
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

bool gameController::isGameOver() {
    if (blackPieces == 0) {
        status = WIN_WHITE;
        return true;
    }
    if (whitePieces == 0) {
        status = WIN_BLACK;
        return true;
    }
    return false;
}

void gameController::game() {
    // Jeśli pierwszy jest czarny to pierwszy, jeśli nie to drugi zaczyna
    currentPlayer = (player1.getPlayerColor() == BLACK) ? &player1 : &player2;

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
                    if (isGameOver()) break;  // Sprawdzenie po każdym ruchu czy jest koniec gry
                }
                switchPlayer();  // Koniec ruchów człowieka(wielokrotne bicie) zmien gracza
            } else {
                status = WRONG_MOVE;
            }
        }

        // Skończył się pierwszy ruch
        firstRun = false;
        updateGameStatus();
    }
}
int gameController::makeAiNetMove() {
    if (firstRun && currentPlayer->getPlayerColor() == WHITE) {
        std::cout << "wychodze" << std::endl;
        return 0;
    }
    if (currentPlayer->getPlayerColor() == player1.getPlayerColor()) {
        // Odebranie ruchu funkcji heurystycznej
        Move aiMove = currentPlayer->getAiMove();
        // Przypisanie ruchów pod odpwiednie indeksy
        int fromRow = aiMove.fromRow;
        int fromCol = aiMove.fromCol;
        int toRow = aiMove.toRow;
        int toCol = aiMove.toCol;
        int fromPos;
        int toPos;

        // Ruch na swojej planszy w celu odchaczenia ruchu
        if (!currentPlayer->makeMove(fromRow, fromCol, toRow, toCol)) {
            return -1;
        }
        // Konwersja indeksów na pozycje 1-32
        fromPos = convertToMoveIndex(fromRow, fromCol);
        toPos = convertToMoveIndex(toRow, toCol);

        // Sprawdzenie, czy ruch jest bicia czy zwykły ruch
        bool isCapture = std::abs(fromRow - toRow) == 2 && std::abs(fromCol - toCol) == 2;

        // Utworzenie stringa z ruchem
        std::string stringPos;
        if (isCapture) {
            stringPos = std::to_string(fromPos) + "x" + std::to_string(toPos);
        } else {
            stringPos = std::to_string(fromPos) + "-" + std::to_string(toPos);
        }

        // Wysłanie stringa przez socket
        if (write(serv_sock, stringPos.c_str(), stringPos.length()) < 0) {
            std::cerr << "Error: Wysłanie ruchu!" << std::endl;
            return -1;
        }
    }
    printf("Czekam na ruch przeciwnika ...\n");

    return 0;
}

int gameController::enemyMove() {
    char buf[BUFSPACE];
    int n = read(serv_sock, buf, sizeof(buf));
    if (n < 0) {
        std::cerr << "Error: Odebranie ruchu!" << std::endl;
        return -1;
    }
    if (n == 0) {
        std::cerr << "Broker zamknął połączenie!" << std::endl;
        return -1;
    }
    buf[n] = 0;
    switchPlayer();
    std::vector<int> positions;
    std::string enemyMove(buf);
    std::cout << "ruch przeciwnika: " << enemyMove << std::endl;
    std::cout << "kolor: " << currentPlayer->getPlayerColor() << std::endl;
    if (parseMove(enemyMove, positions) && positions.size() == 2) {
        int from = positions[0];
        int to = positions[1];
        int fromRow, fromCol, toRow, toCol;
        convertMove(from, fromRow, fromCol);
        convertMove(to, toRow, toCol);
        if (!currentPlayer->makeMove(fromRow, fromCol, toRow, toCol)) {
            std::cerr << "Error: Nieprawidłowy ruch przeciwnika!" << std::endl;
            std::cerr << "tutaj" << std::endl;
            return -1;
        }
    } else {
        std::cerr << "Error: Nieprawidłowy format ruchu przeciwnika!" << std::endl;
        return -1;
    }
    return 0;
}

void gameController::brokerGame() {
    // Przypisanie pod aktualnego gracza AI
    currentPlayer = &player1;
    while (1) {
        // ruch mojego programu, jak błąd zwraca -1
        if (makeAiNetMove() < 0) {
            return;
        }
        if (enemyMove() < 0) {
            return;
        }
        switchPlayer();
        firstRun = false;
    }
}

void gameController::connectToBroker(std::string ipAddress, int ipPort) {
    struct sockaddr_in serv_addr;
    struct hostent* serv_hostent;

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0) {
        perror("socket");
        exit(errno);
    }
    serv_hostent = gethostbyname(ipAddress.c_str());
    if (serv_hostent == 0) {
        fprintf(stderr, "Nieznany adres IP %s\n", ipAddress.c_str());
        exit(-1);
    }
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr, serv_hostent->h_addr, serv_hostent->h_length);
    serv_addr.sin_port = htons(ipPort);

    std::cout << "Łączenie się z serwerem ...\n";
    if (connect(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(-1);
    }
    printf("Polaczenie nawiazane, zaczynamy gre ...\n");
}
