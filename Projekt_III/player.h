#ifndef PLAYER_H
#define PLAYER_H
#include "checkersBoard.h"
#include <chrono>

enum playerType { HUMAN, AI };

class Player {
   public:
    Player(playerType playerType, PieceColor color, CheckersBoard& board);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);
    Move getAiMove(int depth);
    PieceColor getPlayerColor() const;
    playerType getPlayerType() const;

   private:
    int miniMax(CheckersBoard board, int depth, int alpha, int beta, bool maximizingPlayer);
    playerType whoIsPlaying;
    PieceColor playerColor;
    CheckersBoard& board;
};

#endif