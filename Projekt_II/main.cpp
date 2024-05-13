#include "bucketSort.h"
#include "functions.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "readFile.h"

/*================================ MAIN ================================*/
int main(int argc, char *argv[]) {
    // Przechowywujemy zawartość pliku do sortowania
    std::vector<Movie> data;
    // Nazwa pliku
    std::string file_name;
    // Kolumna według, której należy sortować, wartość domyślna 3
    int sort_key_pos = 3;
    // Ilość rzeczy do sortowania
    int n_items = 0;
    // Nazwa algorytmu
    std::string algo_name = "";
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
            algo_name = argv[4];
            if (!isString(algo_name)) {
                std::cerr << "Error: Błędna nazwa algorytmu.: " << algo_name << std::endl;
                return 1;
            }
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
            return 1; // Koniec programu
            
        }
    }
    // Sprawdzenie poprawności parametrów wejściowych
    if (checkInputParameters(sort_key_pos, n_items, shuffle_passes) != 0) return 1;

    // Jeśli nie podano nazwy pliku, wczytaj z wejścia standardowego
    if (file_name == "-") {
        data = loadCinParameters(sort_key_pos, n_items);
    } else if (argc == 1) {
        data = loadCin(sort_key_pos);
        // Domyślny algorytm dla przekierowanego pliku
        algo_name = "QUICK";
    } else {
        data = loadCSV(file_name, sort_key_pos, n_items);
    }
    // Jeśli wektor jest pusty
    if (data.empty()) {
        std::cerr << "Error: Brak danych do sortowania." << std::endl;
        return 1; // Koniec programu
    }
    
    // Przemieszanie kolejności poprawnie wgranych komórek
    shuffle(data, shuffle_passes, shuffle_seed);

    // Rozpoczęcie sortowania
    auto start_time = std::chrono::high_resolution_clock::now();

    // Sortowanie
    if (!sort(data, algo_name)) return 1;

    // Zakończenie sortowania
    auto end_time = std::chrono::high_resolution_clock::now();

    // Wyświetlenie posortowanych wartości wejściowych
    displaySortedData(data);

    // Czas sortowania
    std::chrono::duration<double, std::micro> duration = end_time - start_time;
    std::cerr << std::fixed << std::setprecision(4) << std::endl
              << "Czas sortowania: " << duration.count() / 1000.0 << " milisekund." << std::endl;

    // Obliczanie średniej wartości ratingu
    float averageRating = calculateAverage(data);
    std::cerr << "Średnia wartość ocen: " << std::fixed << std::setprecision(2) << averageRating
              << std::endl;

    // Obliczanie mediany ocen
    float medianRating = calculateMedian(data);
    std::cerr << "Mediana ocen: " << std::fixed << std::setprecision(2) << medianRating
              << std::endl;

    return 0;
}
