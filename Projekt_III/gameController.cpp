#include "gameController.h"

gameController::gameController(CheckersBoard& b) : board(b) {}

void gameController::game() {
    board.printBoard();
}

