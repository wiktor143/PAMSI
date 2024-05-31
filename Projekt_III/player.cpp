#include "player.h"

Player::Player(playerType pT, PieceColor c, CheckersBoard& b)
    : whoIsPlaying(pT), playerColor(c), board(b) {}

bool Player::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (board.isCorrectMove(fromRow, fromCol, toRow, toCol, playerColor)) {
        board.movePiece(fromRow, fromCol, toRow, toCol);
        return true;
    }
    return false;
}

PieceColor Player::getPlayerColor() const { return playerColor; }

playerType Player::getPlayerType() const { return whoIsPlaying; }
