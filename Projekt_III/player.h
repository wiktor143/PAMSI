#ifndef PLAYER_H
#define PLAYER_H
#include "checkersBoard.h"

enum playerType { HUMAN, AI };

class Player {
   public:
    Player(playerType pT, PieceColor c, CheckersBoard& b);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);
    PieceColor getPlayerColor() const;
    playerType getPlayerType() const;

   private:
    playerType whoIsPlaying;
    PieceColor playerColor;
    CheckersBoard& board;
};

#endif