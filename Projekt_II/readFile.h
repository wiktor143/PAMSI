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

// Funkcja do odczytania danych z pliku CSV do vectora
std::vector<Movie> loadCSV(std::string &input_file, int sort_key_pos, int n_items);

// Funkcja do odczytania danych ze standardowego wejścia z argumentami wywołania programu
std::vector<Movie> loadCinParameters(int sort_key_pos, int n_items);

// Funkcja do odczytania danych ze standardowego wejścia przez przekierowanie pliku < "plik.csv"
std::vector<Movie> loadCin(int sort_key_pos);

// Funkcja do podziału każdego wiersza pliku zgodnie z zadanym separatorem '^'
std::vector<std::string> splitRow(const std::string &line, char divider, int sort_key_pos);

// Funkcja zwraca nam ilość separatrów '^' w pliku, aby potem obliczyć ilość komórek w linijce
int getDividerCount(const std::string &line);

// Funkcja sprawdzająca czy odczytana liczba jest typu float
bool isFloat(const std::string &s);
#endif