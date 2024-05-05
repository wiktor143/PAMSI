#include <chrono>
#include <ctime>
#include <iostream>

#include "readFile.h"
/*========================== Prototypy funkcji ==========================*/

// Funkcja zajmująca się sprawdzeniem argumentów podanych przez użytkownika
// w przypadku podania wartości ujemnych, zerowych bądź stringu w miejsce liczby
// zwraca wartość 1 i jest to traktowane jako błąd.
int inputError(int argC, char *argV[]);

// Funkcja do "potasowania" wczytanych elementów.
void shuffle(std::vector<Movie> &data);

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
    // Przemieszanie kolejności poprawnie wgranych komórek.
    shuffle(data);
    // Wyświetlamy wczytane dane dla testu
    // Iteracja po wektorze movies
    std::cout << std::endl;
    for (const auto &movie : data) {
        // Wyświetlenie zawartości text
        std::cout << "Text: ";
        for (const auto &cell : movie.text) {
            std::cout << cell << " ";
        }

        // Wyświetlenie ratingu
        std::cout << "Rating: " << movie.rating << std::endl;

        // Oddzielenie kolejnych filmów
        std::cout << std::endl;
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

void shuffle(std::vector<Movie> &data) {

    // Obiekt do przechowywania wartości w milisekundach
    std::chrono::milliseconds ms;
    // Konwertujemy czas od 1 stycznia 1970 do teraz na milisekundy
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    // Ziarno zainicjowane akutalnym czasem w milisekundach, czyli jego wartość zmienia się z
    // każdą milisekundą
    srand(ms.count());
    
    // Długość wektora 
    int length = static_cast<int>(data.size());

    for (int i = 0; i < length; ++i) {     // Przejdź przez wyszystkie pakiety
        int swap_index = rand() % length;  // Losujemy indeks do podmiany
        Movie temp = data[i];              // Zmienna pomocnicza podczas zamiany
        data[i] = data[swap_index];        // Podmieniamy zawartości pod danymi indeksami
        data[swap_index] = temp;           // Koniec zamiany
    }
}
