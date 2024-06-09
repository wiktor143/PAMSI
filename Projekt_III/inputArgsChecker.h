#ifndef INPUTARGSCHECKER_H
#define INPUTARGSCHECHER_H
#include <iostream>

class inputArgsChecker {
   public:
    inputArgsChecker(int argc, char* argv[]);
    bool isValid() const;
    std::string getInterfaceType() const;
    std::string getTurn() const;
    int getDepth() const;
    long int getRandomSeed() const;
    std::string getIpAddress() const;
    int getIpPort() const;
    void howToUse() const;

   private:
    std::string progName;
    bool valid;
    std::string interfaceType;
    std::string turn;
    int depth;
    long int randomSeed;
    std::string ipAddress;
    int ipPort;
};
#endif