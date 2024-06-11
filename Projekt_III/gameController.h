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
// Status gry: W trakcie, Zakończona przez rezygnację, Nieprawidłowy ruch, Wygrana czarnych, Wygrana
// białych, Remis.
enum gameStatus { RUNNING, QUITED, WRONG_MOVE, WIN_BLACK, WIN_WHITE, DRAFT };

class gameController {
   private:
    CheckersBoard& board;     // Referencja do obiektu planszy do gry.
    Player& player1;          // Referencja do pierwszego gracza.
    Player& player2;          // Referencja do drugiego gracza.
    Player* currentPlayer;    // Wskaźnik do obecnego gracza.
    gameStatus status;        // Aktualny status gry.
    int serv_sock;            // Socket serwera do komunikacji sieciowej.
    bool firstRun;            // Flaga określająca, czy to jest pierwszy ruch.
    int movesWithoutCapture;  // Liczba ruchów bez bicia.
    int blackPieces;          // Liczba czarnych pionków.
    int whitePieces;          // Liczba białych pionków.
    int depth;                // Głębokość analizy dla algorytmu minimax.
    long int randomSeed;      // Ziarno losowe do randomizacji ruchów AI.

    // Konwertuje ruch gracza na współrzędne planszy.
    // Parametry:
    // - row: współrzędna wiersza po konwersji.
    // - col: współrzędna kolumny po konwersji.
    void convertMove(int playerMove, int& row, int& col);

    // Parsuje ruch z formatu tekstowego na listę pozycji.
    // Parametry:
    // - move: ruch w formacie tekstowym.
    // - positions: wektor pozycji na planszy.
    // Zwraca true jeśli parsowanie się powiodło, w przeciwnym razie false.
    bool parseMove(std::string& move, std::vector<int>& positions);

    // Przełącza aktualnego gracza na drugiego gracza.
    void switchPlayer();

    // Aktualizuje status gry na podstawie aktualnego stanu planszy i liczby pionków.
    void updateGameStatus();

    // Wykonuje ruch przez AI, wybierając najlepszy ruch na podstawie algorytmu minimax.
    void makeAiMove();

    // Wykonuje ruch przez AI z wykorzystaniem sieci.
    // Zwraca -1 w przypadku błędu w przeciwnym razie 0.
    int makeAiNetMove();

    // Odczytanie ruchu przeciwnika.
    // Zwraca 0 jeśli ruch odebrany poprawnie, w przeciwnym razie -1.
    int enemyMove();

    // Konwertuje współrzędne planszy na indeks ruchu.
    // Parametry:
    // - row: współrzędna wiersza.
    // - col: współrzędna kolumny.
    // Zwraca indeks ruchu.
    int convertToMoveIndex(int row, int col) const;

    // Pobiera aktualny status gry.
    // Zwraca aktualny status gry.
    gameStatus getGameStatus() const;

    // Sprawdza, czy gra się zakończyła.
    // Zwraca true, jeśli gra się zakończyła, w przeciwnym razie false.
    bool isGameOver();

   public:
    // Konstruktor kontrolera gry.
    // Parametry:
    // - board: referencja do obiektu planszy do gry.
    // - player1: referencja do pierwszego gracza.
    // - player2: referencja do drugiego gracza.
    // - depth: głębokość analizy dla algorytmu minimax.
    // - randomSeed: ziarno losowe do randomizacji ruchów AI.// Konstruktor kontrolera gry.
    gameController(CheckersBoard& board, Player& player1, Player& player2, int depth, long int randomSeed);

    // Główna metoda uruchamiająca grę.
    void game();

    // Metoda uruchamiająca grę w trybie brokera.
    void brokerGame();

    // Łączy się z brokerem.
    // Parametry:
    // - ipAddress: adres IP brokera.
    // - ipPort: port brokera.
    void connectToBroker(std::string ipAddress, int ipPort);
};

#endif