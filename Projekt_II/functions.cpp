#include "functions.h"

int inputError(int argC, char *argV[]) {
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
        return 1;  // Zwróć kod błędu
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

bool isString(const std::string &str) {
    // Sprawdzenie, czy każdy znak w stringu jest literą, jeśli tak to true inaczej false
    if (std::all_of(str.begin(), str.end(), [](char c) { return std::isalpha(c); })) {
        return true;
    } else {
        return false;
    }
    return true;
}

bool sort(std::vector<Movie> &data, std::string &algo_name) {
    if (algo_name == "MERGE") {
        // Zrób sortowanie merge
        mergeSort(data, static_cast<int>(data.size()));
        return true;
    } else if (algo_name == "QUICK") {
        // Zrób quicksort
        quickSort(data, static_cast<int>(data.size()));
        return true;
    } else if (algo_name == "BUCKET") {
        // Zrób sortowanie kubełkowe
        bucketSort(data, static_cast<int>(data.size()));
        return true;
    } else {
        // Przypadek, kiedy nie wpisano nazwy algorytmu, który został zaimplementowany.
        std::cerr << "Error: nie zaimplementowano takiego algorytmu: " << algo_name << std::endl;
        return false;
    }
    return false;
}

float calculateAverage(const std::vector<Movie> &data) {
    float sum = 0.0f;
    for (const auto &movie : data) {
        sum += movie.rating;
    }

    return sum / data.size();  // Średnia wartość
}

float calculateMedian(std::vector<Movie> &data) {
    // Sprawdzenie, czy liczba filmów jest parzysta czy nieparzysta
    size_t n = data.size();
    if (n % 2 == 0) {
        // Jeśli liczba filmów jest parzysta, oblicz medianę jako średnią dwóch środkowych wartości
        return (data[n / 2 - 1].rating + data[n / 2].rating) / 2.0f;
    } else {
        // Jeśli liczba filmów jest nieparzysta, medianą jest wartość środkowego elementu
        return data[n / 2].rating;
    }
}

void displaySortedData(const std::vector<Movie> &data) {
    std::cout << std::endl;
    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
        std::cout << data[i].text[0] << std::endl;
    }
}