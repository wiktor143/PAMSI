#include "Transfer.h"

Transfer::Transfer() {}

void Transfer::sendPackets(Packet *packets, const int length) { shufflePackets(packets, length); }

void Transfer::receivePackets(Packet *packets, int max_packets) {
    for (int i = 0; i < max_packets; i++) {                         // Tworzymy zadaną ilość pakietów
        priorityQueue.push(packets[i].priority, packets[i].packet); // Dodajemy node do naszej kolejki priorytetowej
    }
}

void Transfer::displayReceived() {
    priorityQueue.display(); // Wyświetlamy cała zawartość kolejki priorytetową
    std::cout << std::endl;  // Po wyświetleniu wiadomości zrób spację
}

void Transfer::shufflePackets(Packet *packets, const int length) {
    srand(time(NULL));

    for (int i = 0; i < length; ++i) {     // Przejdź przez wyszystkie pakiety 
        int swap_index = rand() % length;  // Losujemy indeks do podmiany
        Packet temp = packets[i];          // Zmienna pomocnicza podczas zamiany
        packets[i] = packets[swap_index];  // Podmieniamy zawartości pod danymi indeksami
        packets[swap_index] = temp;        // Koniec zamiany 
    }
}

void Transfer::displayShuffledPackets(Packet *packets, const int length) {
    std::cout << "=============================SENT==============================" << std::endl;
    for (int i = 0; i < length; ++i) { // Wyświetlamy zawartość każdego pakietu
        std::cout << packets[i].packet;
    }
    std::cout << std::endl
              << "===========================RECEIVED============================"
              << std::endl;
}

void Transfer::freeMemeory() { 
    priorityQueue.clear(); // Zwalniamy pamięc zaalokowaną dla kolejki priorytetowej
 }