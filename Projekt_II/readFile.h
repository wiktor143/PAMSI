#ifndef READ_F_H
#define READ_F_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Struktura przechowywująca pojedyńczy wiersz pliku
struct Movie {
    std::vector<std::string> text;  // Zawartość całego wiersza podzielona na stringi
    float rating;                   // Ocena
};

// Funkcja wczytuje dane z pliku CSV do wektora struktur Movie. Przyjmuje trzy argumenty: ścieżkę do
// pliku CSV, pozycję kolumny, według której dane będą sortowane, oraz liczbę elementów do
// wczytania. Wczytuje wiersze z pliku, dzieli je na komórki na podstawie separatora '^', a
// następnie przekształca odpowiednią komórkę na wartość liczbową i dodaje dane do wektora. Funkcja
// zwraca ten wektor.
std::vector<Movie> loadCSV(std::string &input_file, int sort_key_pos, int n_items);

// Funkcja wczytuje dane ze standardowego wejścia (terminalu) z argumentami wywołania programu.
// Przyjmuje dwa argumenty: pozycję kolumny, według której dane będą sortowane, oraz liczbę
// elementów do wczytania. Wczytuje wiersze z konsoli, dzieli je na komórki na podstawie separatora
// '^', a następnie przekształca odpowiednią komórkę na wartość liczbową i dodaje dane do wektora.
// Funkcja zwraca ten wektor.
std::vector<Movie> loadCinParameters(int sort_key_pos, int n_items);

// Funkcja ta wczytuje dane ze standardowego wejścia (terminalu) przez przekierowanie pliku( ./prog < "plik.csv"). 
// Przyjmuje jeden argument: pozycję kolumny, według której dane będą sortowane.
// Wczytuje wiersze z konsoli, dzieli je na komórki na podstawie separatora '^', a następnie
// przekształca odpowiednią komórkę na wartość liczbową i dodaje dane do wektora. Funkcja zwraca ten wektor.
std::vector<Movie> loadCin(int sort_key_pos);

// Jest to funkcja pomocnicza do podziału każdego wiersza tekstu na pojedyncze komórki na podstawie separatora '^'.
// Przyjmuje trzy argumenty: wiersz tekstu do podziału, separator oraz pozycję kolumny, według której dane będą sortowane.
// Funkcja zwraca wektor podzielonych stringów.
std::vector<std::string> splitRow(const std::string &line, char divider, int sort_key_pos);

// Ta funkcja zwraca liczbę separatorów w danym wierszu tekstu, co umożliwia obliczenie liczby komórek. 
// Przyjmuje jeden argument: wiersz tekstu. Zwraca liczbę separatorów.
int getDividerCount(const std::string &line);

// Funkcja ta sprawdza, czy dany ciąg znaków jest liczbą zmiennoprzecinkową. 
// Przyjmuje jeden argument: string do sprawdzenia.
// Zwraca true, jeśli ciąg jest liczbą, w przeciwnym razie zwraca false.
bool isNumber(const std::string &s);
#endif