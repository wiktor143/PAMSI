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

Move Player::getAiMove() {
    std::vector<Move> bestMoves;
    int bestValue = -10000;

    for (auto& move : board.getAllPossibleMoves(playerColor)) {
        CheckersBoard newBoard = board;
        newBoard.movePiece(move.fromRow, move.fromCol, move.toRow, move.toCol);
        int boardValue = miniMax(newBoard, 8 - 1, -10000, 10000, false);  // Zaczynamy od minimalizującego przeciwnika
        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMoves.clear();
            bestMoves.push_back(move);
        } else if (boardValue == bestValue) {
            bestMoves.push_back(move);
        }
    }

    if (!bestMoves.empty()) {
        srand(time(NULL));
        int randomIndex = rand() % bestMoves.size();  // Losowy indeks w zakresie 0 do bestMoves.size() - 1
        return bestMoves[randomIndex];
    }
    // Brak dostępnych ruchów, zwraca ruch, który nie jest poprawny
    return {-1, -1, -1, -1};
}

int Player::miniMax(CheckersBoard board, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0) {
        return board.evaluateBoard(playerColor);
    }

    if (maximizingPlayer) {
        int maxEval = -10000;
        for (auto& move : board.getAllPossibleMoves(BLACK)) {
            CheckersBoard newBoard = board;
            newBoard.movePiece(move.fromRow, move.fromCol, move.toRow, move.toCol);
            int eval = miniMax(newBoard, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        for (auto& move : board.getAllPossibleMoves(WHITE)) {
            CheckersBoard newBoard = board;
            newBoard.movePiece(move.fromRow, move.fromCol, move.toRow, move.toCol);
            int eval = miniMax(newBoard, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}