#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
// Struktura przechowywująca pojedyńczy wiersz pliku
struct Movie {
    int id;             // Numer porządkowy
    std::string movie;  // Nazwa filmu
    float rating;       // Ocena
};

// Funkcja pomocnicza do wczytania danych z pliku CSV do vectora
std::vector<Movie> loadCSV(std::string &input_file, int sort_key_pos, int n_items);

std::vector<Movie> loadCinParameters(int sort_key_pos, int n_items);

std::vector<Movie> loadCin();
// Funkcja do podziału każdego wierwsza pliku zgodnie z podanym separatorem
std::vector<std::string> splitRow(const std::string &line, char divider);

