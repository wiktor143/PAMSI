#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "checkersBoard.h"

class gameController {
   private:
    CheckersBoard &board;

   public:
    gameController(CheckersBoard &board);
    void game();
};

#endif