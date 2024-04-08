#ifndef TRANSFER_H
#define TRANSFER_H
#include "PriorityQueue.h"
#include "ReadFile.h"
class Transfer {
   private:
    PriorityQueue priorityQueue;

   public:
    // Konstruktor
    Transfer();
    // Funkcja służąca do symulacji wysyłania pakietów.
    // Po koleji dodaje "potasowane" pakiety przez shufflePackets
    // do kolejki priorytetowej, gdzie następnie są one ustawiane
    // według priorytetu.

    void sendPacket(Packet *packets, int length);
    // Funkcja służąca do wyświetlenia kolejki priorytetowej, czyli
    // naszych pakietów według priorytetu.
    void displayReceived();

    // Funckcja służąca do zwolnienia pamięci zajmowanej przez
    // kolejkę priorytetową.
    void freeMemeory();
};

#endif