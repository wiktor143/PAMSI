#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "checkersBoard.h"
#include "player.h"

enum gameStatus { RUNNING, QUITED, WRONG_MOVE, WIN_BLACK, WIN_WHITE, DRAFT };

class gameController {
   private:
    CheckersBoard& board;
    Player& player1;
    Player& player2;
    Player* currentPlayer;
    gameStatus status;
    void convertMove(int playerMove, int& row, int& col);
    bool parseMove(std::string& move, std::vector<int>& positions);
    bool firstRun;
    void switchPlayer();
    void updateGameStatus();
    void makeAiMove();
    int convertToMoveIndex(int row, int col) const;
    gameStatus getGameStatus() const;
    bool isGameOver();
    int movesWithoutCapture;
    int blackPieces;
    int whitePieces;

   public:
    gameController(CheckersBoard& board, Player& player1, Player& player2);
    void game();
};

#endif