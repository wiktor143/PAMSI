#ifndef TRANSFER_H
#define TRANSFER_H
#include "PriorityQueue.h"
#include "ReadFile.h"

class Transfer {
   private:
    // Tworzymy kolejkę prioytetową
    PriorityQueue priorityQueue;

    // Funkcja do "potasowania" pakietów przed symulacją odebrania.
    void shufflePackets(Packet *packets, const int length);

   public:
    // Konstruktor
    Transfer();

    // Funkcja służąca do symulacji wysyłania pakietów.
    // Zamienia kolejnością utworzone pakiety za pomocą prywatnej funkcji shufflePackets()
    void sendPackets(Packet *packets, const int length);

    // Funkcja służąca do symulacji odebrania pakietów.
    // Po koleji dodaje "potasowane" pakiety przez shufflePackets
    // do prywatnej kolejki priorytetowej, gdzie następnie są one ustawiane według priorytetu.
    void receivePackets(Packet *packets, int max_packets);

    // Funkcja służąca do wyświetlenia kolejki priorytetowej, czyli
    // naszych pakietów według priorytetu.
    void displayReceived();

    // Funckcja służąca do zwolnienia pamięci zajmowanej przez
    // kolejkę priorytetową.
    void freeMemeory();

    // Funkcja do wyświetlenia "potasowanych" pakietów przed wysłaniem.
    void displayShuffledPackets(Packet *packets, const int length);
};

#endif