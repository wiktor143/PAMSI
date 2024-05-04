#include "readFile.h"

std::vector<Movie> loadCSV(std::string &input_file, int sort_key_pos, int n_items) {
    std::ifstream file(input_file);  // Plik, z którego mamy czytać dane
    std::vector<Movie> data;         // Dane: liczba porządkowa, nazwa, rating
    std::string line;                // Buffer na zawartość wiersza
    int count = 0;                   // liczba wczytanych wierszy

    if (!file.is_open()) {  // Sprawdzamy czy plik został otworzony poprawnie
        std::cerr << "Error: Nie można otworzyć pliku: " << input_file << std::endl;
        return data;  // Zwracamy pusty wektor
    }
    // Sprawdzamy, czy plik jest pusty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: Plik jest pusty: " << input_file << std::endl;
        return data;  // Zwracamy pusty wektor
    }

    while (std::getline(file, line) && count < n_items) {
        // Pobieramy każdy wiersz z pliku do momentu, kiedy count
        // będzie równy zadanej wartości argumentu wywołania, count startuje od 0 dlatego < n_items

        // Odczytujemy wiersz
        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        // W przypadku kiedy klucz sortowania jest większy niż ilość komórek występuje błąd
        std::vector<std::string> parsedData = splitRow(line, '^', sort_key_pos);

        // Pominięcie pustych linii bądź takich, w których nie występuje rating
        if (!parsedData.empty()) {
            try {
                // Rating filmu
                // Próba zamiany strimga na floata, jeśli się nie powiedzie
                // program pominie tą linijkę i wychwyci wyjątek
                float rating = std::stof(parsedData[sort_key_pos - 1]);
                // Dodanie całej poziomej linii oraz ratingu do wektora przechowywującego
                // informację
                data.push_back({parsedData, rating});
                // Zwiększenie liczby poprawnie odczytanych wierszy
                count++;
            } catch (const std::invalid_argument &) {
                // Nieudana konwersja, nie zwiększa nam liczby wierszy
            }
        }
    }

    // Powielanie poprawnie wczytanych wcześniej filmów
    for (int i = 0; i < (n_items - count); i++) {
        data.push_back(data[i]);
    }
    return data;  // Zwracamy wektor
}

std::vector<Movie> loadCinParameters(int sort_key_pos, int n_items) {
    std::vector<Movie> data;  // Dane: liczba porządkowa, nazwa, rating
    std::string line;         // Buffer na zawartość wiersza
    int count = 0;            // liczba wczytanych wierszy

    while (std::getline(std::cin, line) && count < n_items) {
        // Pobieramy każdy wiersz z pliku do momentu, kiedy count
        // będzie równy zadanej wartości argumentu wywołania, count startuje od 0 dlatego < n_items

        // Odczytujemy wiersz
        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        // W przypadku kiedy klucz sortowania jest większy niż ilość komórek występuje błąd
        std::vector<std::string> parsedData = splitRow(line, '^', sort_key_pos);

        // Pominięcie pustych linii bądź takich, w których nie występuje rating
        if (!parsedData.empty()) {
            try {
                // Rating filmu
                // Próba zamiany strimga na floata, jeśli się nie powiedzie
                // program pominie tą linijkę i wychwyci wyjątek
                float rating = std::stof(parsedData[sort_key_pos - 1]);
                // Dodanie całej poziomej linii oraz ratingu do wektora przechowywującego
                // informację
                data.push_back({parsedData, rating});
                // Zwiększenie liczby poprawnie odczytanych wierszy
                count++;
            } catch (const std::invalid_argument &) {
                // Nieudana konwersja, nie zwiększa nam liczby wierszy
            }
        }
    }

    // Powielanie poprawnie wczytanych wcześniej filmów
    for (int i = 0; i < (n_items - count); i++) {
        data.push_back(data[i]);
    }
    return data;  // Zwracamy wektor
}

std::vector<Movie> loadCin() {
    std::vector<Movie> data;  // Dane: liczba porządkowa, nazwa, rating
    std::string line;         // Buffer na zawartość wiersza
    int count = 0;            // liczba wczytanych wierszy

    while (std::getline(std::cin, line)) {
        // Pobieramy każdy wiersz z pliku do momentu, kiedy count
        // będzie równy zadanej wartości argumentu wywołania, count startuje od 0 dlatego <
        // n_items
        // Odczytujemy wiersz
        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        std::vector<std::string> parsedData = splitRow(line, '^', 3);
        // Pominięcie pustych linii bądź takich, w których nie występuje rating
        if (!parsedData.empty()) {
            try {
                // Rating filmu
                // Próba zamiany strimga na floata, jeśli się nie powiedzie
                // program pominie tą linijkę i wychwyci wyjątek
                float rating = std::stof(parsedData[2]);
                // Dodanie całej poziomej linii oraz ratingu do wektora przechowywującego
                // informację
                data.push_back({parsedData, rating});
                // Zwiększenie liczby poprawnie odczytanych wierszy
                count++;
            } catch (const std::invalid_argument &) {
                // Nieudana konwersja, nie zwiększa nam liczby wierszy
            }
        }
    }
    return data;
}

std::vector<std::string> splitRow(const std::string &line, char divider, int sort_key_pos) {
    // Podzielony wiersz, każda komórka to kawałek tekstu
    // oddzielonego separatorem '^'
    std::vector<std::string> separatedData;

    // Buffer na wycinek tekstu
    std::string buffer;

    // Strumień o typie stringa, podobne do std::cin, ale
    // zamiast czytać ze standardowego wejścia czytamy ze stringa
    std::istringstream stringToRead(line);

    // Ilość separatorów, ilość komórek jest zawsze większa niż ilość '^'
    int cellsCount = getDividerCount(line) + 1;

    // Sprawdzamy czy klucz sortowania nie jest większy niż ilość dostępnych komórek
    if (sort_key_pos > cellsCount) {
        std::cerr << "Error: Klucz sortowania jest większy niż ilość dostępnych komórek."
                  <<cellsCount<< std::endl;
        return separatedData;
    }

    // Pętla umożliwiająca wycięcie ratinug ze stringa
    while (std::getline(stringToRead, buffer, divider)) {
        // Dodanie podzielonych komórek
        separatedData.push_back(buffer);
    }
    // Porównanie rozmiaru wektora z rozmiarem, który powinien być.
    // Użyto jawnej konwersji int'a na size_type
    if (separatedData.size() != static_cast<std::vector<int>::size_type>(cellsCount)) {
        separatedData.clear();
        return separatedData;
    }
    // Zwracamy podzielony wiersz
    return separatedData;
}

int getDividerCount(const std::string &line) {
    // Separatorów
    int num = std::count(line.begin(), line.end(), '^');
    return num;
}