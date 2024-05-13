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
    // Pętla wczytująca wiersze z pliku
    while (std::getline(file, line) && count < n_items) {
        // Odczytujemy wiersz

        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        std::vector<std::string> parsedData = splitRow(line, '^', sort_key_pos);

        // Pominięcie pustych linii bądź takich, w których tytył zaczyna się od cyfry.
        // Ważne aby sprawdzić rozmiar wektora, aby isFloat nie odwołał się do nie istniejącego indeksu
        if (!parsedData.empty() && parsedData.size() == 2 && isNumber(parsedData[1])) {
            try {
                // Rating filmu
                // Próba zamiany stringa na float, jeśli się nie powiedzie, pomiń linijkę
                float rating = std::stof(parsedData[1]);
                // Dodanie całej poziomej linii oraz ratingu do wektora przechowywującego informację
                data.push_back({parsedData, rating});
                // Zwiększenie liczby poprawnie odczytanych wierszy
                count++;
            } catch (const std::invalid_argument &) {
                // Nieudana konwersja, nie zwiększa nam liczby wierszy
            }
        }
    }

    // Powielanie poprawnie wczytanych wcześniej filmów, jeśli nie ma danych do powielenia pomijamy kopiowanie.
    if (count != 0) {
        for (int i = 0; i < (n_items - count); i++) {
            data.push_back(data[i]);
        }
    }

    return data;  // Zwracamy wektor
}

std::vector<Movie> loadCinParameters(int sort_key_pos, int n_items) {
    std::vector<Movie> data;  // Dane: liczba porządkowa, nazwa, rating
    std::string line;         // Buffer na zawartość wiersza
    int count = 0;            // liczba wczytanych wierszy

    // Pętla wczytująca wiersze z wejścia
    while (std::getline(std::cin, line) && count < n_items) {
        // Odczytujemy wiersz

        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        std::vector<std::string> parsedData = splitRow(line, '^', sort_key_pos);

        // Pominięcie pustych linii bądź takich, w których tytył zaczyna się od cyfry.
        // Ważne aby sprawdzić rozmiar wektora, aby isFloat nie odwołał się do nie istniejącego indeksu
        if (!parsedData.empty() && parsedData.size() == 2 && isNumber(parsedData[1])) {
            try {
                // Rating filmu
                // Próba zamiany stringa na float, jeśli się nie powiedzie, pomiń linijkę
                float rating = std::stof(parsedData[1]);
                // Dodanie całej poziomej linii oraz ratingu do wektora przechowywującego informację
                data.push_back({parsedData, rating});
                // Zwiększenie liczby poprawnie odczytanych wierszy
                count++;
            } catch (const std::invalid_argument &) {
                // Nieudana konwersja, nie zwiększa nam liczby wierszy
            }
        }
    }

    // Powielanie poprawnie wczytanych wcześniej filmów, jeśli nie ma danych do powielenia pomijamy kopiowanie.
    if (count != 0) {
        for (int i = 0; i < (n_items - count); i++) {
            data.push_back(data[i]);
        }
    }

    return data;  // Zwracamy wektor
}

std::vector<Movie> loadCin(int sort_key_pos) {
    std::vector<Movie> data;  // Dane: liczba porządkowa, nazwa, rating
    std::string line;         // Buffer na zawartość wiersza
    int count = 0;            // liczba wczytanych wierszy

    while (std::getline(std::cin, line)) {
        // Odczytujemy wiersz

        // Podział całego wiersza na pojedyńcze komórki według zadanego separatora
        std::vector<std::string> parsedData = splitRow(line, '^', sort_key_pos);
        
        // Pominięcie pustych linii bądź takich, w których tytył zaczyna się od cyfry.
        // Ważne aby sprawdzić rozmiar wektora, aby isFloat nie odwołał się do nie istniejącego indeksu
        if (!parsedData.empty() && parsedData.size() == 2 && isNumber(parsedData[1])) {
            try {
                // Rating filmu
                // Próba zamiany stringa na float, jeśli się nie powiedzie, pomiń linijkę
                float rating = std::stof(parsedData[1]);
                // Dodanie całej poziomej linii oraz ratingu do wektora przechowywującego informację
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
    // Podzielony wiersz, każda komórka to kawałek tekstu oddzielonego separatorem '^'
    std::vector<std::string> separatedData;

    // Buffer na wycinek tekstu
    std::string allText;
    // Buffer na wycięty rating
    std::string rating;

    // Strumień o typie stringa, podobne do std::cin, ale
    // zamiast czytać ze standardowego wejścia czytamy ze stringa
    std::istringstream stringToRead(line);

    // Ilość separatorów, ilość komórek jest zawsze większa niż ilość '^'
    int cellsCount = getDividerCount(line) + 1;

    // Licznik separatorów
    int dividerCounter = 0;

    // Czytamy całą zawartość wiersza
    std::getline(stringToRead, allText);

    // Dodajemy do wektora na pierwsze miejsce
    separatedData.push_back(allText);

    // Przesuwamy wskaźnik na początek strumienia, aby w dalszej kolejności odczytać rating
    stringToRead.seekg(0);

    // Sprawdzamy czy klucz sortowania nie jest większy niż ilość dostępnych komórek.
    // Jeśli tak jest zwraca nam pusty wektor
    if (sort_key_pos > cellsCount) {
        return separatedData;
    }

    // Pętla umożliwiająca wycięcie ratinug ze stringa
    while (std::getline(stringToRead, rating, divider)) {
        // Dodanie podzielonych komórek
        if (dividerCounter == sort_key_pos - 1) {
            separatedData.push_back(rating);
        }
        dividerCounter++;
    }

    // Porównanie rozmiaru wektora z rozmiarem, który powinien być.
    // Wartość dwa, ponieważ poprawny wektora powinien mieć pod indeksem nr 0
    // całą zawartość wiersza natomiast pod indeksem 1 sam rating
    if (static_cast<int>(separatedData.size()) != 2) {
        separatedData.clear();
        return separatedData;
    }
    // Zwracamy podzielony wiersz
    return separatedData;
}

int getDividerCount(const std::string &line) {
    
    // Ilość separatorów w linijce
    int num = std::count(line.begin(), line.end(), '^');
    return num;
}

bool isNumber(const std::string &s) {

    // Zmienne czy znaleziono kropke i czy jest to cyfra
    bool decimalPointFound = false;
    bool digitFound = false;

    // Przechodzimy przez całego stringa
    for (char c : s) {
        // Czy jest to cyfra, jeśli tak to zmienna digitFoung jest true
        if (std::isdigit(c)) {
            digitFound = true;
            // Jeśli to nie cyfra, musi być to kropka
        } else if (c == '.') {
            // Znaleziono już wcześniej kropkę, jeśli tak to zwróc false
            if (decimalPointFound) {
                // Mamy już jedną kropkę dziesiętną
                return false;
            }
            // Jeśli wcześniej kropki nie było, zapisz, że kropka została znaleziona
            decimalPointFound = true;
        } else {
            // Znaleziono znak niebędący cyfrą ani kropką
            return false;
        }
    }

    // Musimy mieć co najmniej jedną cyfrę i nie więcej niż jedną kropkę
    return (digitFound && decimalPointFound) || (digitFound && !decimalPointFound);
}