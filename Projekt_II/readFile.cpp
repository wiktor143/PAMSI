#include "readFile.h"

std::vector<Movie> loadCSV(std::string &input_file, int sort_key_pos, int n_items) {
    std::ifstream file(input_file);  // Plik, z którego mamy czytać dane
    std::vector<Movie> data;         // Dane: liczba porządkowa, nazwa, rating
    std::string line;                // Buffer na zawartość wiersza
    int count = 0;                   // liczba wczytanych wierszy
    int numFields = std::count(line.begin(), line.end(), '^') + 1; // Liczba pól

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
        std::vector<std::string> parsedData = splitRow(line, '^');

        try {
            // Numer porządkowy
            int id = std::stoi(parsedData[0]);
            // Nazwa filmu
            std::string movie = parsedData[1];
            // Rating filmu
            // Próba zamiany strimga na floata, jeśli się nie powiedzie
            // program pominie tą linijkę i wychwyci wyjątek
            float rating = std::stof(parsedData[sort_key_pos - 1]);
            data.push_back({id, movie, rating});
            count++;
        } catch (const std::invalid_argument &) {
            // Nieudana konwersja, nie zwiększa nam liczby wierszy
        }
    }

    // Powielanie poprawnie wczytanych już filmów
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
        std::vector<std::string> parsedData = splitRow(line, '^');
        try {
            // Numer porządkowy
            int id = std::stoi(parsedData[0]);

            // Nazwa filmu
            std::string movie = parsedData[1];
            // Rating filmu
            // Próba zamiany strimga na floata, jeśli się nie powiedzie
            // program pominie tą linijkę i wychwyci wyjątek

            float rating = std::stof(parsedData[sort_key_pos - 1]);

            data.push_back({id, movie, rating});

            count++;
        } catch (const std::invalid_argument &) {
            // Nieudana konwersja, nie zwiększa nam liczby wierszy
        }
    }

    // Powielanie poprawnie wczytanych już filmów
    for (int i = 0; i < (n_items - count); i++) {
        data.push_back(data[i]);
    }
    return data;
}
std::vector<Movie> loadCin() {
    std::vector<Movie> data;  // Dane: liczba porządkowa, nazwa, rating
    std::string line;         // Buffer na zawartość wiersza
    int count = 0;            // liczba wczytanych wierszy

    while (std::getline(std::cin, line)) {
        // Pobieramy każdy wiersz z pliku do momentu, kiedy count
        // będzie równy zadanej wartości argumentu wywołania, count startuje od 0 dlatego < n_items
        // Odczytujemy wiersz
        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        std::vector<std::string> parsedData = splitRow(line, '^');
        try {
            // Numer porządkowy
            int id = std::stoi(parsedData[0]);

            // Nazwa filmu
            std::string movie = parsedData[1];
            // Rating filmu
            // Próba zamiany strimga na floata, jeśli się nie powiedzie
            // program pominie tą linijkę i wychwyci wyjątek

            float rating = std::stof(parsedData[2]);

            data.push_back({id, movie, rating});

            count++;
        } catch (const std::invalid_argument &) {
            // Nieudana konwersja, nie zwiększa nam liczby wierszy
        }
    }
    return data;
}

std::vector<std::string> splitRow(const std::string &line, char divider) {
    // Podzielony wiersz, każda komórka to kawałek tekstu
    // oddzielonego separatorem '^'
    std::vector<std::string> separatedData;

    // Buffer na wycinek tekstu
    std::string buffer;

    // Strumień o typie stringa, podobne do std::cin, ale
    // zamiast czytać ze standardowego wejścia czytamy ze stringa
    std::istringstream stringToRead(line);

    // Podział oddczytanego wiersza na komórki
    while (std::getline(stringToRead, buffer, divider)) {
        // Dodanie podzielonej komórki danego wiersza
        separatedData.push_back(buffer);
    }

    // Zwracamy podzielony wiersz
    return separatedData;
}