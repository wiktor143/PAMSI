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
    Player player1(HUMAN, WHITE, board);
    Player player2(AI, BLACK, board);
    gameController ctrl(board, player1, player2);

    // Obsługa GUI i NET
    if (argsChecker.getInterfaceType() == "GUI") {
        ctrl.game();
    } else if (argsChecker.getInterfaceType() == "NET") {
        std::cout << "narazie nie ma" << std::endl;
    }

    return 0;
}