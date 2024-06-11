#include "inputArgsChecker.h"

// Konstruktor klasy inputArgsChecker
inputArgsChecker::inputArgsChecker(int argc, char* argv[])
    : valid(false), randomSeed(0), ipAddress("localhost"), ipPort(12345) {
    // Przypisanie nazwy programu
    progName = argv[0];
    // Sprawdzenie liczby argumentów, jeśli jest niepoprawna, zwraca false
    if (argc < 4 || argc > 7) {
        return;
    }
    if (argc == 6) {
        return;
    }
    // Przypisanie wartości argumentów do zmiennych 
    try {
        interfaceType = argv[1];
        turn = argv[2];
        depth = std::atoi(argv[3]);
        if (argc >= 5) {
            randomSeed = std::atoi(argv[4]);
        }
        if (argc == 7) {
            ipAddress = argv[5];
            ipPort = std::atoi(argv[6]);
        }
    } catch (const std::invalid_argument& ERROR) {
        std::cerr << "Error: Podano błędne argumenty wywołania: " << ERROR.what()
                  << std::endl;  // Wystąpił błąd
        return;
    }
    // Sprawdzenie poprawności argumentów
    if ((interfaceType == "GUI" || interfaceType == "NET") &&
        (turn == "WHITE" || turn == "BLACK") && depth > 0) {
        valid = true;
    }
}

// Metoda sprawdzająca, czy argumenty wejściowe są poprawne.
bool inputArgsChecker::isValid() const { return valid; }

// Metoda zwracająca typ interfejsu określony przez argumenty wejściowe.
std::string inputArgsChecker::getInterfaceType() const { return interfaceType; }

// Metoda zwracająca, który gracz zaczyna grę określony przez argumenty wejściowe.
std::string inputArgsChecker::getTurn() const { return turn; }

// Metoda zwracająca głębokość analizy algorytmu określoną przez argumenty wejściowe.
int inputArgsChecker::getDepth() const { return depth; }

// Metoda zwracająca ziarno losowe określone przez argumenty wejściowe.
long int inputArgsChecker::getRandomSeed() const { return randomSeed; }

// Metoda zwracająca adres IP określony przez argumenty wejściowe.
std::string inputArgsChecker::getIpAddress() const { return ipAddress; }

// Metoda zwracająca numer portu określony przez argumenty wejściowe.
int inputArgsChecker::getIpPort() const { return ipPort; }

// Metoda wyświetlająca informacje o tym, jak używać programu.
void inputArgsChecker::howToUse() const {
    std::cerr << "Poprawne wywołanie programu:" << std::endl << "  " << progName << " interface turn depth [random_seed] [ip_address ip_port]" << std::endl;
}
