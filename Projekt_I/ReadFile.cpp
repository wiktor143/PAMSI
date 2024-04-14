#include "ReadFile.h"

int MaxPacketsCount(int message_size, int packet_size) {
    // Obliczamy ilość pakietów
    int num_packets = message_size / packet_size;

    // Jeśli rozmiar całej wiadomości nie jest podzielny bez reszty przez rozmiar
    // pakietu, dodajemy jeden pakiet na resztę danych
    if (message_size % packet_size != 0) {
        num_packets++;
    }
    return num_packets; // Zwraca ilość pakietów 
}

int readPackets(const std::string &file_name, int offset, int message_size, int packet_size, Packet *packets, int max_packets) {
    std::string buffer;             // Buffer, do którego kolejno dodawane są char'y, aby potem stworzyć jeden pakiet
    std::ifstream file(file_name);  // Plik, z którego mamy czytać tekst 
    int current_msg_size = 0;       // Aktulna wielkość wiadomości
    if (!file.is_open()) {          // Sprawdzamy czy plik został otworzony poprawnie
        std::cerr << "Error: Nie można otworzyć pliku: " << file_name << std::endl;
        return 1;  // Przerywamy działanie progrmau
    }
    // Sprawdzamy, czy plik jest pusty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: Plik jest pusty: " << file_name << std::endl;
        return 1;  // Przerywamy działanie programu
    }

    // Przypadek gdy offset jest > 0
    if (offset > 0) {
        file.seekg(offset, std::ios::beg);  // Przesuwamy kursor od początku pliku o zadany offset
        // Przypadek gdy użytkownik chce wylosować wartość offset
    } else if (offset == -1) {
        srand(time(NULL));
        int temp_offset = rand() % 10000;        // Losowanie wartości offset'u
        file.seekg(temp_offset, std::ios::beg);  // Przesuwamy kursor od początku pliku o wylosowany offset
    }

    for (int i = 0; i < max_packets; ++i) { // Tworzymy zadaną ilość pakietów
        Packet packet; // Za każdym razem tworzymy nowy pakiet 
        char buffer;   // Do przechwycenia char'a
        for (int j = 0; j < packet_size; ++j) { // Pętla aż do zadanej ilości bajtów jednego pakietu
            // Jeśli wielkość wiadomości nie została przekroczona odczytać znak
            if (file.get(buffer) && message_size > current_msg_size) { // Jeśli nie EOF i aktualna wiadomości mniejsza niż zadana
                packet.packet += buffer; // Dodaj char'a
                current_msg_size++;      // Zwiększ rozmiar wiadomości o jeden
            } else if (file.eof()) {           // Jeśli napotkaliśmy koniec pliku 
                file.clear();                  // Wyczyść flagę EOF
                file.seekg(0, std::ios::beg);  // Przesuń kursor na początek pliku
                j--;                           // W przypadku końca pliku, jeden char jest wtedy pomijany i wiadomośc byłaby za krótka
            }
        }
        packet.priority = i + 1;  // Nadajemy priorytet wpisania pakietu
        packets[i] = packet;      // Dodajemy pakiet do naszej tablicy przed wysłaniem
    }

    file.close();  // Zamykamy strumień

    return 0;
}
