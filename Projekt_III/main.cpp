#include <iostream>

#include "checkersBoard.h"
#include "gameController.h"
#include "inputArgsChecker.h"
#include "player.h"

int main(int argc, char *argv[]) {
    // Utworzenie obiektu argsChecker w celu sprawdzenia argumentów wejściowych
    inputArgsChecker argsChecker(argc, argv);

    // Zmienna do przechowywania ziarna generatora liczb losowych
    long int seed;

    // Sprawdzenie poprawności argumentów
    if (!argsChecker.isValid()) {
        argsChecker.howToUse();  // Wyświetlenie instrukcji użycia, jeśli argumenty są niepoprawne
        return 1;
    }

    // Generowanie ziarna
    if (argsChecker.getRandomSeed() == 0) {
        // Konwertujemy czas od 1 stycznia 1970 do teraz na milisekundy, jeśli ziarno nie jest
        // podane
        seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                   .count();
    } else if (argsChecker.getRandomSeed() != 0) {
        // Używamy podanego ziarna
        seed = argsChecker.getRandomSeed();
    }

    // Inicjalizacja generatora
    srand(seed);

    // Utworzenie planszy do gry
    CheckersBoard board;

    // Przypisanie odpowiednich kolorów graczom
    // Jeśli podano "WHITE", AI gra białymi, w przeciwnym razie gra czarnymi
    PieceColor aiColor = (argsChecker.getTurn()) == "WHITE" ? WHITE : BLACK;
    // Człowiek gra przeciwnym kolorem do AI
    PieceColor humanColor = (aiColor == WHITE) ? BLACK : WHITE;

    // Utworzenie graczy: AI i człowieka
    Player player1(AI, aiColor, board);
    Player player2(HUMAN, humanColor, board);
    // Utworzenie kontrolera gry
    gameController ctrl(board, player1, player2, argsChecker.getDepth(), argsChecker.getRandomSeed());

    // Obsługa trybów : GUI i NET
    if (argsChecker.getInterfaceType() == "GUI") {
        ctrl.game();  // Rozpoczęcie gry w trybie GUI

    } else if (argsChecker.getInterfaceType() == "NET") {
        ctrl.connectToBroker(argsChecker.getIpAddress(), argsChecker.getIpPort());  // Połączenie z serwerem
        ctrl.brokerGame();                              // Rozpoczęcie gry w trybie sieciowym
    }
    return 0;
}