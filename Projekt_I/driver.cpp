#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>

#include "ReadFile.h"
#include "Transfer.h"

/*========================== Prototypy funkcji ==========================*/

// Funkcja zajmująca się sprawdzeniem argumentów podanych przez użytkownika
// w przypadku podania wartości ujemnych, zerowych bądź stringu w miejsce liczby
// zwraca wartość 1 i jest to traktowane jako błąd.
int inputError(int argC, char *argV[]);

/*================================ MAIN ================================*/
int main(int argc, char *argv[]) {
    
    // Obiekt do obsługi przesyłu danych
    Transfer transferManager;

    // Sprawdzenie czy podano dobre argumenty wejścia
    if (inputError(argc, argv) != 0) return 1;  // Błąd wywołania, koniec programu

    // Wczytujemy argumenty pod odpowiednie zmienne
    std::string file_name = argv[1];
    int offset = std::stoi(argv[2]);  // Konwersja argumentu na liczbę
    int message_size = std::stoi(argv[3]);
    int packet_size = std::stoi(argv[4]);
    int additional_parameter;  // Parametr do wyświetlenia wiadomości
    if (argc == 6) additional_parameter = std::stoi(argv[5]); // Jeśli jest 6 argumentów konwertuj dodatkowy parametr

    const int MAX_PACKETS = MaxPacketsCount(message_size, packet_size);  // Obliczamy liczbę pakietów
    Packet *packets = new Packet[MAX_PACKETS];                           // Alokujmey pamięc dla tablicy

    // Przetwarzamy pakiety
    if (readPackets(file_name, offset, message_size, packet_size, packets, MAX_PACKETS) != 0)
        return 1;

    transferManager.sendPackets(packets, MAX_PACKETS);
    // Jeśli podano dodatkowy parametr wyświetl "potasowane" pakiety
    if (additional_parameter == 1) transferManager.displayShuffledPackets(packets, MAX_PACKETS);

    // Moment rozpoczęcia wysyłania
    auto start_time = std::chrono::high_resolution_clock::now();

    // Uporządkowanie odebranych pakietów według priorytetu
    transferManager.receivePackets(packets, MAX_PACKETS);

    // Wyświetlamy odebrane pakiety na wyjście standardowe
    transferManager.displayReceived();

    // Koniec symulacji odbierania pakietów
    auto end_time = std::chrono::high_resolution_clock::now();

    transferManager.freeMemeory();

    // Obliczamy ile trwała symulacja
    std::chrono::duration<double, std::micro> duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Czas trwania- w milisekundach
    std::cout << std::endl << "Czas działania algorytmu w milisekundach:" << std::endl;
    std::cout << duration.count() / 1000.0 << std::endl;

    delete[] packets;  // Usunięcie pamięci dla packets
    return 0;
}

/*============================ Dodatkowe funkcje ============================*/

int inputError(int argC, char *argV[]) {
    // Sprawdzamy, czy podano odpowiednią ilość argumentów podczas wywołania drivera
    if (argC != 5 && argC != 6) {
        std::cerr << "Poprawne wywołanie programu: " << argV[0]
                  << " file_name file_offset message_size packet_size" << std::endl
                  << "bądź" << std::endl
                  << "Poprawne wywołanie programu: " << argV[0]
                  << " file_name file_offset message_size packet_size 1" << std::endl;
        return 1;  // Zwróć kod błędu
    }
    for (int i = 2; i < argC; ++i) {
        int num;

        try {
            num = std::stoi(argV[i]);  // Próba konwersji argumentu na liczbę
        } catch (const std::invalid_argument &ERROR) {  // Jeśli użytkownik podał stringa podczas wywołania
            std::cerr << "Error: argument musi być liczbą: " << ERROR.what() << std::endl;  // Wystąpił błąd
            return 1;
        } catch (...) {
            std::cerr << "Error: program napotkał problem" << std::endl; // Poinformowanie użytkownika o błędzie
            return 1;
        }

        // Sprawdzenie, jakie zostały podane argumenty, jeśli są ujemne bądź wynoszą zero wystąpi błąd
        switch (i) {
            case 2:  // Offset
                if (num < -1) {
                    std::cerr << "Error: offset nie może być mniejszy od -1" << std::endl;
                    return 1;
                }
                break;
            case 3:  // Message_size
                if (num < 0) {
                    std::cerr << "Error: message_size nie może być ujemny" << std::endl;
                    return 1;
                }
                if (num == 0) {
                    std::cerr << "Error: Nie można wysłać wiadomości message_size = 0" << std::endl;
                    return 1;
                }
                break;
            case 4:  // Packet_size
                if (num < 0) {
                    std::cerr << "Error: packet_size nie może być ujemny " << std::endl;
                    return 1;
                }
                if (num == 0) {
                    std::cerr << "Error: Nie można wysłać wiadomości pakiet_size = 0" << std::endl;
                    return 1;
                }
                break;
            case 5: // Dodatkowy parametr
                if (num != 1) {
                    std::cerr << "Error: Dodatkowy parametr musi wynosić 1" << std::endl;
                    return 1;
                }
                break;

            default:
                break;
        }
    }
    return 0;
}
