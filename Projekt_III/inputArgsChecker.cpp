#include "inputArgsChecker.h"

inputArgsChecker::inputArgsChecker(int argc, char* argv[])
    : valid(false), randomSeed(0), ipAddress("localhost"), ipPort(12345) {
    progName = argv[0];
    std::cout << "argc: " << argc << std::endl;
    if (argc < 4 || argc > 7) {
        return;
    }

    try {
        interfaceType = argv[1];
        turn = argv[2];
        depth = std::atoi(argv[3]);
        if (argc == 5) {
            randomSeed = std::atoi(argv[4]);
        }
        std::cout << "czytanie arg: " << randomSeed << std::endl;
        if (argc == 7) {
            ipAddress = argv[5];
            ipPort = std::atoi(argv[6]);
        }
    } catch (const std::invalid_argument& ERROR) {
        std::cerr << "Error: Podano błędne argumenty wywołania: " << ERROR.what()
                  << std::endl;  // Wystąpił błąd
        return;
    }
    if ((interfaceType == "GUI" || interfaceType == "NET") &&
        (turn == "WHITE" || turn == "BLACK") && depth > 0) {
        valid = true;
    }
}

bool inputArgsChecker::isValid() const { return valid; }

std::string inputArgsChecker::getInterfaceType() const { return interfaceType; }

std::string inputArgsChecker::getTurn() const { return turn; }

int inputArgsChecker::getDepth() const { return depth; }

long int inputArgsChecker::getRandomSeed() const { return randomSeed; }

std::string inputArgsChecker::getIpAddress() const { return ipAddress; }

int inputArgsChecker::getIpPort() const { return ipPort; }

void inputArgsChecker::howToUse() const {
    std::cerr << "Poprawne wywołanie programu:" << std::endl
              << "  " << progName << " interface turn depth [random_seed] [ip_address ip_port]"
              << std::endl;
}
