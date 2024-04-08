#include "Transfer.h"

Transfer::Transfer(){};

void Transfer::sendPacket(Packet *packets, int length) {
    for (int i = 0; i < length; i++) {
        priorityQueue.push(packets[i].priority, packets[i].packet);
    }
}

void Transfer::displayReceived(){
    priorityQueue.display();
}

void Transfer::freeMemeory(){
    priorityQueue.clear();
}