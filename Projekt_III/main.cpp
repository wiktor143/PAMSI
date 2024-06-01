#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "checkersBoard.h"
#include "gameController.h"
#include "inputArgsChecker.h"
#include "player.h"

#define BUFSPACE 1024
int main(int argc, char *argv[]) {
    inputArgsChecker argsChecker(argc, argv);
    if (!argsChecker.isValid()) {
        argsChecker.howToUse();
        return 1;
    }

    CheckersBoard board;
    // Przypisanie odpowiednich kolorów graczą, jeśli podany został biały, ai gra białymi
    PieceColor aiColor = (argsChecker.getTurn()) == "WHITE" ? WHITE : BLACK;
    // Jeśli ai białe to człowiek gra czarnymi
    PieceColor humanColor = (aiColor == WHITE) ? BLACK : WHITE;

    Player player1(AI, aiColor, board);
    Player player2(HUMAN, humanColor, board);
    gameController ctrl(board, player1, player2);

    // Obsługa GUI i NET
    if (argsChecker.getInterfaceType() == "GUI") {
        ctrl.game();

    } else if (argsChecker.getInterfaceType() == "NET") {
        char buf[BUFSPACE];
        int serv_sock, n;
        struct sockaddr_in serv_addr;
        struct hostent *serv_hostent;

        serv_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (serv_sock < 0) {
            perror("socket");
            exit(errno);
        }
        serv_hostent = gethostbyname(argsChecker.getIpAddress().c_str());
        if (serv_hostent == 0) {
            fprintf(stderr, "Nieznany adres IP %s\n", argsChecker.getIpAddress().c_str());
            exit(-1);
        }
        serv_addr.sin_family = AF_INET;
        memcpy(&serv_addr.sin_addr, serv_hostent->h_addr, serv_hostent->h_length);
        serv_addr.sin_port = htons(argsChecker.getIpPort());

        std::cout << "Łączenie się z serwerem ...\n";
        if (connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("connect");
            exit(-1);
        }
        printf("Polaczenie nawiazane, zaczynamy gre ...\n");
    }

    return 0;
}