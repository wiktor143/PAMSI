#include "ReadFile.h"

int MaxPacketsCount(int message_size, int packet_size) {
    // Obliczamy ilość pakietów
    int num_packets = message_size / packet_size;

    // Jeśli rozmiar całej wiadomości nie jest dokładnie podzielny przez rozmiar
    // pakietu, dodajemy jeden pakiet na resztę danych
    if (message_size % packet_size != 0) {
        num_packets++;
    }
    return num_packets; 
}

int readPackets(const std::string &file_name, int offset, int packet_size,
                Packet *packets, int max_packets) {
    std::string buffer;             // Zawartość pakietu
    std::ifstream file(file_name);  // Nasz plik

    if (!file.is_open()) {  // Sprawdzamy czy plik został otworzony
        std::cerr << "Error: Nie można otworzyć pliku: " << file_name
                  << std::endl;
        return 1;  // Przerywamy działanie progrmau
    }

    if(offset > 0){
        for(int i = 0; i < offset; ++i)
        {
            file.get(); // Pomijamy ilość znaków równą offset
        }
    }
    for (int i = 0; i < max_packets; ++i) {
        Packet packet;
        char buffer; // Do przechwycenia chara
        for (int j = 0; j < packet_size; ++j) {
            if (file.get(buffer)) {
                packet.packet += buffer;
            } else {
                break;  // W przypadku błędu lub końca pliku przerywamy pętlę
            }
        }
        packet.priority = i + 1;  // Nadajemy priorytet wpisania pakietu
        packets[i] = packet;

        if (file.eof()) {
            break;  // Kończymy wczytywanie, jeśli dotarliśmy do końca pliku
        }
    }

    file.close(); // Zamykamy strumień

    return 0;
}
