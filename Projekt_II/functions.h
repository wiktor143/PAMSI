#ifndef FUNC
#define FUNC

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "bucketSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "readFile.h"

// Funkcja sprawdza poprawność argumentów przekazanych przez użytkownika do programu.
// Jeśli ilość argumentów wywołania jest spoza zakresu <2;7>, lub jest równa 1
// (czyli sam nazwa programu). Jeśli ilość argumentów wywołania zawiera się w przedziale <2;5>
// również jest błąd, funkcja wyświetla instrukcję uruchomienia programu, informując użytkownika o
// poprawnym formacie, oraz zwraca kod błędu 1. W przeciwnym razie zwraca 0, sygnalizując brak
// błędów.
int inputError(int argC, char *argV[]);

// Funkcja do "potasowania" wczytanych elementów, zadaną ilość razy.
// Może też przyjąć wartość ziarna (shuffle_seed) dla generatora liczb pseudolosowych
// , co pozwala na kontrolowanie powtarzalności wyników tasowania.
void shuffle(std::vector<Movie> &data, int shuffle_passes, int shuffle_seed);

// Funkcja sprawdza poprawność parametrów wejściowych programu, takich jak
// pozycja klucza sortowania (sort_key_pos), liczba elementów (n_items) oraz liczba
// przejść w procesie tasowania (shuffle_passes). Zapewnia, że wartości są dodatnie.
int checkInputParameters(int sort_key_pos, int n_items, int shuffle_passes);

// Funkcja wykonuje sortowanie danych w wektorze zgodnie z wybranym algorytmem, którego
// nazwa jest przekazana jako argument (algo_name). Obsługiwane algorytmy to "MERGE" (sortowanie
// przez scalanie), "QUICK" (sortowanie szybkie) i "BUCKET" (sortowanie kubełkowe). Funkcja zwraca
// true, jeśli sortowanie zostało wykonane poprawnie, a w przeciwnym razie false.
bool sort(std::vector<Movie> &data, std::string &algo_name);

// Funkcja sprawdza, czy dany ciąg znaków jest poprawnym stringiem, tzn. czy
// składa się wyłącznie z liter. Zwraca true, jeśli wszystkie znaki w ciągu są literami, a w
// przeciwnym razie false.
bool isString(const std::string &str);

// Funkcja oblicza średnią wartość ratingu dla wszystkich
// filmów zawartych w wektorze data i zwraca tę wartość.
float calculateAverage(const std::vector<Movie> &data);

// Funkcja oblicza medianę wartości dla ratingudla wszystkich filmów zawartych w wektorze
// data i zwraca tę wartość.
float calculateMedian(std::vector<Movie> &data);

// Funkcja wyświetla posortowane dane
void displaySortedData(const std::vector<Movie> &data);
#endif