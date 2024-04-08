#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "ReadFile.h"
#include "Transfer.h"

// Funkcja zajmująca się sprawdzeniem argumentów podanych przez użytkownika
// w przypadku podania wartości ujemnych bądź zerowych zwraca wartość
// 1 i jest to traktowane jako błąd.
int inputError(int argC, char *argV[]);

// Funkcja do "potasowania" pakietów przed symulacją wysłania.
void shufflePackets(Packet *packets, const int length);

// Funkcja do wyświetlenia "potasowanych" pakietów.
void displayShuffledPackets(Packet *packets, const int length);
int main(int argc, char *argv[]) {
    Transfer transferManager;
    // Sprawdzamy, czy podano odpowiednią ilość argumentów podczas wywołania
    // drivera
    if (inputError(argc, argv) != 0)
        return 1;  // Błąd wywołania, koniec programu

    // Wczytujemy argumenty pod odpowiednie zmienne
    std::string file_name = argv[1];
    int offset = std::stoi(argv[2]);  // Konwersja argumentu na liczbę
    int message_size = std::stoi(argv[3]);
    int packet_size = std::stoi(argv[4]);

    // W przypadku gdy packet_size jest większe od message_size zwracamy błąd
    if (packet_size > message_size) {
        std::cerr << "Error: packet_size nie może być większe od message_size";
        return 1;
    }

    std::cout << "Argumenty wywołania funkcji: " << std::endl;
    std::cout << "File name: " << file_name << std::endl;
    std::cout << "File offset: " << offset << std::endl;
    std::cout << "Message size: " << message_size << std::endl;
    std::cout << "Packet size: " << packet_size << std::endl << std::endl;

    const int MAX_PACKETS = MaxPacketsCount(
        message_size, packet_size);  // Obliczamy liczbę pakietów
    std::cout << "Maksymalna ilośc pakietów: "<< MaxPacketsCount(message_size, packet_size);
    Packet *packets = new Packet[MAX_PACKETS];  // alokujmey pamięc dla tablicy
    std::cout << " | pamieć zarezerwowana dla Packet*MAX_PACKETS: "<< sizeof(Packet) * MAX_PACKETS << std::endl<< std::endl;

    // // Przetwarzamy pakiety
    if (readPackets(file_name, offset, message_size, packet_size, packets,
                    MAX_PACKETS) != 0)
        return 1;
    shufflePackets(packets, MAX_PACKETS);
    displayShuffledPackets(packets, MAX_PACKETS);
    transferManager.sendPacket(packets, MAX_PACKETS);
    transferManager.displayReceived();
    transferManager.freeMemeory();

    delete[] packets;

    return 0;
}

// Dodatkowe funkcje
int inputError(int argC, char *argV[]) {
    // Sprawdzamy, czy podano odpowiednią ilość argumentów podczas wywołania
    // drivera
    if (argC != 5) {
        std::cerr << "Poprawne wywołanie programu: " << argV[0]
                  << " file_name file_offset message_size packet_size"
                  << std::endl;
        return 1;  // Zwróć kod błędu
    }
    for (int i = 2; i < argC; ++i) {
        int num = std::stoi(argV[i]);  // Zamieniamy argument na liczbę
        // Sprawdzenie jakie zostały podane argumenty
        switch (i) {
            case 2:  // Offset
                if (num < -1) {
                    std::cerr << "Error: offset nie może być mniejszy od -1"
                              << std::endl;
                    return 1;
                }
                break;
            case 3:  // Message_size
                if (num < 0) {
                    std::cerr << "Error: message_size nie może być ujemny"
                              << std::endl;
                    return 1;
                }
                if (num == 0) {
                    std::cerr
                        << "Error: Nie można wysłać wiadomości message_size = 0"
                        << std::endl;
                    return 1;
                }
                break;
            case 4:  // Packet_size
                if (num < 0) {
                    std::cerr << "Error: packet_size nie może być ujemny "
                              << std::endl;
                    return 1;
                }
                if (num == 0) {
                    std::cerr
                        << "Error: Nie można wysłać wiadomości pakiet_size = 0"
                        << std::endl;
                    return 1;
                }
                break;

            default:
                break;
        }
    }
    return 0;
}

void shufflePackets(Packet *packets, const int length) {
    srand(time(NULL));

    for (int i = 0; i < length; ++i) {
        int swap_index = rand() % length;  // Losujemy indeks do podmiany
        Packet temp = packets[i];          // Zmienna pomocnicza podczas zamiany
        packets[i] =
            packets[swap_index];  // Podmieniamy zawartości pod danymi indeksami
        packets[swap_index] = temp;
    }
}

void displayShuffledPackets(Packet *packets, const int length) {
    std::cout << std::endl
              << "=============================================WYSLANE========="
                 "===================================="
              << std::endl
              << std::endl;
    for (int i = 0; i < length; ++i) {
        std::cout << packets[i].packet;
    }
    std::cout << std::endl
              << std::endl
              << "=============================================ODEBRANE========"
                 "====================================="
              << std::endl
              << std::endl;
}