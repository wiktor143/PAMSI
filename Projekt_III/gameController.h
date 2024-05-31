#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "checkersBoard.h"
#include "player.h"

enum gameStatus { RUNNING, QUITED, WRONG_MOVE, WIN, LOST, DRAFT };

class gameController {
   private:
    CheckersBoard& board;
    Player& player1;
    Player& player2;
    Player* currentPlayer;
    gameStatus status;
    int movesWithoutCapture;
    void convertMove(int playerMove, int& row, int& col);
    bool parseMove(std::string& move, std::vector<int>& positions);
    void switchPlayer();
    gameStatus getGameStatus() const;

   public:
    gameController(CheckersBoard& board, Player& player1, Player& player2);
    void game();
};

#endif