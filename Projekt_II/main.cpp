#include <iostream>

#include "readFile.h"
/*========================== Prototypy funkcji ==========================*/

// Funkcja zajmująca się sprawdzeniem argumentów podanych przez użytkownika
// w przypadku podania wartości ujemnych, zerowych bądź stringu w miejsce liczby
// zwraca wartość 1 i jest to traktowane jako błąd.
int inputError(int argC, char *argV[]);

/*================================ MAIN ================================*/
int main(int argc, char *argv[]) {
    // Przechowywujemy zawartość pliku do sortowania
    std::vector<Movie> data;
    // Nazwa pliku
    std::string file_name;
    // Kolumna według, której należy sortować
    int sort_key_pos;
    // Ilość rzeczy do sortowania
    int n_items;

    // Sprawdzenie czy podano dobre argumenty wejścia
    if (inputError(argc, argv) != 0) return 1;  // Błąd wywołania, koniec programu

    // Jeśli nie mamy przekierowania ./prog < "nazwa.csv"
    if (argc != 1) {
        file_name = argv[1];
        sort_key_pos = std::stoi(argv[2]);
        n_items = std::stoi(argv[3]);
    }
    // Sprawdzamy wartość klucza do sortowania, jeśli wychodzi z naszego przedziału <1;3>
    // przerywamy działanie pod warunkiem, że jest więcej argumentów wywołania niż 1
    if (argc != 1 && (sort_key_pos > 3 || sort_key_pos <= 0)) {
        std::cerr << "Error: Klucz sortowania jest z przedziału <1;3>. Podany klucz: "
                  << sort_key_pos << std::endl;
        return 1;
    }
    if (file_name == "-") {
        data = loadCinParameters(sort_key_pos, n_items);
    } else if (argc == 1) {
        data = loadCin();
    } else {
        data = loadCSV(file_name, sort_key_pos, n_items);
    }
    if (data.empty()) {
        std::cerr << "Error: Brak danych do sortowania." << std::endl;
    }

    // Wyświetlamy wczytane dane dla testu
    for (const auto &row : data) {
        std::cout << "ID: " << row.id << ", Film: " << row.movie << ", Ocena: " << row.rating
                  << std::endl;
    }
    return 0;
}

int inputError(int argC, char *argV[]) {
    // Sprawdzamy, czy podano odpowiednią ilość argumentów podczas wywołania drivera
    if (argC != 6 && argC != 1) {
        std::cerr << "Poprawne wywołanie programu: " << argV[0]
                  << " input_file_name sort_key_pos n_items algo_name shuffle_passes" << std::endl;
        return 1;  // Zwróć kod błędu
    }
    return 0;
}
