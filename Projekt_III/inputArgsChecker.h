#ifndef INPUTARGSCHECKER_H
#define INPUTARGSCHECHER_H
#include <iostream>

class inputArgsChecker {
   private:
    std::string progName;       // Nazwa programu.
    bool valid;                 // Zmienna przechowująca informację o poprawności argumentów.
    std::string interfaceType;  // Typ interfejsu.
    std::string turn;           // Informacja o tym, który gracz zaczyna.
    int depth;                  // Głębokość analizy algorytmu.
    long int randomSeed;        // Ziarno losowe.
    std::string ipAddress;      // Adres IP.
    int ipPort;                 // Numer portu.

   public:
    // Konstruktor klasy przyjmujący liczbę argumentów oraz tablicę argumentów.
    // Parametry:
    // - argc: Liczba argumentów.
    // - argv: Tablica argumentów.
    inputArgsChecker(int argc, char* argv[]);

    // Metoda sprawdzająca, czy argumenty wejściowe są poprawne.
    // Zwraca true, jeśli argumenty są poprawne, w przeciwnym razie false.
    bool isValid() const;

    // Metoda zwracająca typ interfejsu określony przez argumenty wejściowe.
    // Zwraca typ interfejsu jako string.
    std::string getInterfaceType() const;

    // Metoda zwracająca, który gracz zaczyna grę określony przez argumenty wejściowe.
    // Zwraca "black" jeśli zaczyna czarny, w przeciwnym razie "white".
    std::string getTurn() const;

    // Metoda zwracająca głębokość analizy algorytmu określoną przez argumenty wejściowe.
    // Zwraca głębokość analizy jako int.
    int getDepth() const;

    // Metoda zwracająca ziarno losowe określone przez argumenty wejściowe.
    // Zwraca ziarno losowe jako long int.
    long int getRandomSeed() const;

    // Metoda zwracająca adres IP określony przez argumenty wejściowe.
    // Zwraca adres IP jako string.
    std::string getIpAddress() const;

    // Metoda zwracająca numer portu określony przez argumenty wejściowe.
    // Zwraca numer portu jako int.
    int getIpPort() const;

    // Metoda wyświetlająca informacje o tym, jak używać programu.
    void howToUse() const;
};
#endif