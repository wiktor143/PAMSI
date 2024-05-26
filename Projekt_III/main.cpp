#include <iostream>

#include "checkersBoard.h"
#include "gameController.h"

int main() {
    CheckersBoard board;
    gameController ctrl(board);

    ctrl.game();
    return 0;
}