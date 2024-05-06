#include <chrono>
#include <ctime>
#include <iostream>

#include "readFile.h"
#include "mergeSort.h"
/*========================== Prototypy funkcji ==========================*/

// Funkcja zajmująca się sprawdzeniem argumentów podanych przez użytkownika
// w przypadku podania wartości ujemnych, zerowych bądź stringu w miejsce liczby
// zwraca wartość 1 i jest to traktowane jako błąd.
int inputError(int argC, char *argV[]);

// Funkcja do "potasowania" wczytanych elementów.
void shuffle(std::vector<Movie> &data, int shuffle_passes, int shuffle_seed);

// Funkcja sprawdzająca czy nie zostały podane ujemne wartości parametrów
int checkInputParameters(int sort_key_pos, int n_items, int shuffle_passes);

/*================================ MAIN ================================*/
int main(int argc, char *argv[]) {
    // Przechowywujemy zawartość pliku do sortowania
    std::vector<Movie> data;
    // Nazwa pliku
    std::string file_name;
    // Kolumna według, której należy sortować, wartość domyślna 3
    int sort_key_pos = 3;
    // Ilość rzeczy do sortowania
    int n_items;
    // Liczba przebiegów mieszania danych, wartość domyślna 0
    int shuffle_passes = 0;
    // Ziarno generatora liczb losowych, wartość domyślna 0
    int shuffle_seed = 0;
    // Sprawdzenie czy podano dobre argumenty wejścia
    if (inputError(argc, argv) != 0) return 1;  // Błąd wywołania, koniec programu

    // Jeśli nie mamy przekierowania ./prog < "nazwa.csv"
    if (argc != 1) {
        try {
            file_name = argv[1];
            sort_key_pos = std::stoi(argv[2]);
            n_items = std::stoi(argv[3]);
            // Jeśli korzystamy z dodatkowych parametrów wywołania
            if (argc == 6 || argc == 7) {
                shuffle_passes = std::stoi(argv[5]);
            }
            if (argc == 7) {
                shuffle_seed = std::stoi(argv[6]);
            }
            // Jeśli np. podano stringa zamiast liczby jest zwracany błąd programu
        } catch (const std::invalid_argument &ERROR) {
            std::cerr << "Error: Podano błędne argumenty wywołania: " << ERROR.what()
                      << std::endl;  // Wystąpił błąd
            return 1;
            // Nieudana konwersja
        }
    }
    if (checkInputParameters(sort_key_pos, n_items, shuffle_passes) != 0) return 1;

    if (file_name == "-") {
        data = loadCinParameters(sort_key_pos, n_items);
    } else if (argc == 1) {
        data = loadCin(sort_key_pos);
    } else {
        data = loadCSV(file_name, sort_key_pos, n_items);
    }
    if (data.empty()) {
        std::cerr << "Error: Brak danych do sortowania." << std::endl;
        return 1;
    }
    // Przemieszanie kolejności poprawnie wgranych komórek.
    shuffle(data, shuffle_passes, shuffle_seed);
    //mergeSort(data, static_cast<int>(data.size()));
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
    // Sprawdzamy, czy podano odpowiednią ilość argumentów podczas wywołania programu

    // Jeśli podano więcej niż jeden argument wywołania czyli samą nazwę programu, zwracana jest
    // instrukcja uruchomieniowa programu, ten warunek jest potrzebny w przypadku przekierowania
    // pliku < "plik.csv". Jeśli ilość argumentów wywołania zawiera się w przedziale <2;5> również
    // jest błąd, ponieważ jest to niewystarczająca liczba argumentów. W koncu przypadek, kiedy
    // liczba argumentów przewyższy 7.
    if ((argC < 1 || argC > 7) || (argC > 1 && argC < 5)) {
        std::cerr
            << "Poprawne wywołanie programu: " << std::endl
            << "      " << argV[0]
            << " input_file_name sort_key_pos n_items algo_name [shuffle_passes] [shuffle_seed]"
            << std::endl
            << "bądź: " << argV[0]
            << " - sort_key_pos n_items algo_name [shuffle_passes] [shuffle_seed]" << std::endl
            << "bądź: " << argV[0] << " < input_file_name" << std::endl;
        return 1;  // Zwróć kodma błędu
    }
    return 0;
}

void shuffle(std::vector<Movie> &data, int shuffle_passes, int shuffle_seed) {
    // Obiekt do przechowywania wartości w milisekundach
    std::chrono::milliseconds ms;

    if (shuffle_seed == 0) {
        // Konwertujemy czas od 1 stycznia 1970 do teraz na milisekundy
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    } else if (shuffle_seed != 0) {
        ms = std::chrono::milliseconds(shuffle_seed);
    }
    std::cout << ms.count() << std::endl;

    // Ziarno zainicjowane akutalnym czasem w milisekundach, czyli jego wartość zmienia się z
    // każdą milisekundą
    srand(ms.count());
    // Długość wektora
    int length = static_cast<int>(data.size());

    // Jeśli wartość parametru shuffle_passes jest równa zero to nie mieszamy kolejności
    // w jakiej odczytano dane
    for (int j = 0; j < shuffle_passes; j++) {
        for (int i = 0; i < length; ++i) {     // Przejdź przez wyszystkie pakiety
            int swap_index = rand() % length;  // Losujemy indeks do podmiany
            Movie temp = data[i];              // Zmienna pomocnicza podczas zamiany
            data[i] = data[swap_index];        // Podmieniamy zawartości pod danymi indeksami
            data[swap_index] = temp;           // Koniec zamiany
        }
    }
}

int checkInputParameters(int sort_key_pos, int n_items, int shuffle_passes) {
    // Sprawdzenie poprawności argumentów wywołania
    if (sort_key_pos <= 0) {
        std::cerr << "Error: Podano błędny klucz sortowania." << std::endl;
        return 1;
    }
    if (n_items < 0) {
        std::cerr << "Error: Podano błędną liczbę elementów do wczytania." << std::endl;
        return 1;
    }
    if (shuffle_passes < 0) {
        std::cerr << "Error: Podano błędną liczbę przebiegów mieszania." << std::endl;
        return 1;
    }
    return 0;
}
