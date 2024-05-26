#include "gameController.h"

gameController::gameController(CheckersBoard& b) : board(b) {
    // Rozpoczęcie gry
    status = RUNNING;
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
            int position = std::stoi(positionBuffer);
            positions.push_back(position);
        } catch (...) {
            // W przypadku podania złego znaku zwróć false
            return false;
        }
    }
    return true;
}

void gameController::game() {
    while (status == RUNNING) {
        board.printBoard();

        std::cout << "Podaj ruch (np. 1x6 lub 11x18x25) lub 'q' aby zakończyć: ";
        std::string move;
        std::vector<int> positions;
        std::cin >> move;
        if (move == "q") {
            status = FINISHED;
        }

        if (parseMove(move, positions)) {
            bool validMove = true;
            for (int i = 0; i < static_cast<int>(positions.size() - 1); ++i) {
                int from = positions[i];
                int to = positions[i + 1];
                int fromRow, fromCol, toRow, toCol;
                convertMove(from, fromRow, fromCol);
                convertMove(to, toRow, toCol);
                std::cout << "From: Row: " << fromRow << ", Col: " << fromCol << std::endl;
                std::cout << "To: Row: " << toRow << ", Col: " << toCol << std::endl;
                board.movePiece(fromRow,fromCol,toRow,toCol);
            }
            if (!validMove) {
                std::cout << "Nieprawidłowy ruch!" << std::endl;
            }
        } else {
            std::cout << "Nieprawidłowy format ruchu!" << std::endl;
            status = FINISHED;
        }
    }
    std::cout << std::endl;
}
