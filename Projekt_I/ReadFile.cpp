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

int readPackets(const std::string &file_name, int offset, int message_size,
                int packet_size, Packet *packets, int max_packets) {
    std::string buffer;             // Zawartość pakietu
    std::ifstream file(file_name);  // Nasz plik
    int current_msg_size = 0;       // Aktulna wielkość wiadomości
    if (!file.is_open()) {          // Sprawdzamy czy plik został otworzony
        std::cerr << "Error: Nie można otworzyć pliku: " << file_name
                  << std::endl;
        return 1;  // Przerywamy działanie progrmau
    }
    // Sprawdzamy, czy plik jest pusty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: Plik jest pusty: " << file_name << std::endl;
        return 1;  // Przerywamy działanie programu
    }
    // Przypadek gdy offset jest > 0
    if (offset > 0) {
        file.seekg(
            offset,
            std::ios::beg);  // Przesuwamy kursor od początku pliku o offset
        // Przypadek gdy użytkownik chce wylosować wartość offset
    } else if (offset == -1) {
        srand(time(NULL));
        int temp_offset = rand() % 10000;
        file.seekg(temp_offset, std::ios::beg);  // Przesuwamy kursor od początku pliku o
                                    // wylosowany offset
    }

    for (int i = 0; i < max_packets; ++i) {
        Packet packet;
        char buffer;  // Do przechwycenia chara
        for (int j = 0; j < packet_size; ++j) {
            // Jeśli wielkość wiadomości nie została przekroczona odczytać znak
            if (file.get(buffer) && message_size > current_msg_size) {
                packet.packet += buffer;
                current_msg_size++;
                // std::cout << "Message_size: " << message_size
                //           << " | Actuall message_size: " << current_msg_size
                //           << std::endl;
            } else if (file.eof()) {
                file.clear();  // Wyczyszczenie flag błędów
                file.seekg(0, std::ios::beg);  // Przesunięcie kursora na początek pliku
                j--;  // Przypadek końca pliku, jeden char jest wtedy pomijany
            }
        }
        packet.priority = i + 1;  // Nadajemy priorytet wpisania pakietu
        packets[i] = packet;
    }

    file.close();  // Zamykamy strumień

    return 0;
}
