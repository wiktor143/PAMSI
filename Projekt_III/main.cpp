#include <iostream>

#include "checkersBoard.h"
#include "gameController.h"
#include "inputArgsChecker.h"
#include "player.h"

int main(int argc, char *argv[]) {
    inputArgsChecker argsChecker(argc, argv);
    if (!argsChecker.isValid()) {
        argsChecker.howToUse();
        return 1;
    }

    CheckersBoard board;
    // Przypisanie odpowiednich kolorów graczą, jeśli podany został biały, ai gra białymi
    PieceColor aiColor = (argsChecker.getTurn()) == "WHITE" ? WHITE : BLACK;
    // Jeśli ai białe to człowiek gra czarnymi
    PieceColor humanColor = (aiColor == WHITE) ? BLACK : WHITE;

    Player player1(AI, aiColor, board);
    Player player2(HUMAN, humanColor, board);
    gameController ctrl(board, player1, player2);

    // Obsługa GUI i NET
    if (argsChecker.getInterfaceType() == "GUI") {
        ctrl.game();

    } else if (argsChecker.getInterfaceType() == "NET") {
        ctrl.connectToBroker(argsChecker.getIpAddress(), argsChecker.getIpPort());
        ctrl.brokerGame();
    }
    return 0;
}