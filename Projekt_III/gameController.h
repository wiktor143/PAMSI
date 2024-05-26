#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "checkersBoard.h"

enum gameStatus {RUNNING, FINISHED, WIN, LOST, DRAFT};

class gameController {
   private:
    CheckersBoard &board;
    gameStatus status;
    void convertMove(int playerMove, int& row, int& col);
    bool parseMove(std::string &move, std::vector<int> &positions);


   public:
    gameController(CheckersBoard &board);
    void game();
};

#endif