#ifndef READFILE_H
#define READFILE_H
#include <fstream>
#include <iostream>

// Struktura jednego pakietu
struct Packet {
    // Zmienna do przechowywania pakietu
    std::string packet;
    // Priorytet
    unsigned int priority;
};

// Funkcja służąca do odczytania pliku podanego przez użytkownika
// oraz podzielenia tekstu na "N" obliczonych pakietów
// przez MaxPacketsCount oraz "zapakowania" odpowiedniej ilości bajtów do pakietu.
// W sytuacji błędu zwraca wartość 1.
int readPackets(const std::string &file_name, int offset, int message_size, int packet_size, Packet *packets, int max_packets);

// Funkcja obliczająca ilość maksymalnych pakietów na podstawie message_size oraz packet_size.
// Zwraca ilość pakietów
int MaxPacketsCount(int message_size, int packet_size);

#endif