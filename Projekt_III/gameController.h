#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>

#include "checkersBoard.h"
#include "player.h"

#define BUFSPACE 1024

enum gameStatus { RUNNING, QUITED, WRONG_MOVE, WIN_BLACK, WIN_WHITE, DRAFT };

class gameController {
   private:
    CheckersBoard& board;
    Player& player1;
    Player& player2;
    Player* currentPlayer;
    gameStatus status;
    int serv_sock;
    void convertMove(int playerMove, int& row, int& col);
    bool parseMove(std::string& move, std::vector<int>& positions);
    bool firstRun;
    void switchPlayer();
    void updateGameStatus();
    void makeAiMove();
    int makeAiNetMove();
    int enemyMove();
    int convertToMoveIndex(int row, int col) const;
    gameStatus getGameStatus() const;
    bool isGameOver();
    int movesWithoutCapture;
    int blackPieces;
    int whitePieces;
    int depth;
    long int randomSeed;

   public:
    gameController(CheckersBoard& board, Player& player1, Player& player2, int depth, long int randomSeed);
    void game();
    void brokerGame();
    void connectToBroker(std::string ipAddress, int ipPort);
};

#endif