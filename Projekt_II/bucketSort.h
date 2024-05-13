#ifndef BUCKET_SORT
#define BUCKET_SORT

#include"readFile.h"

// Funkcja sortująca dane wejściowe w sposób kubełkowy(bucket sort).
void bucketSort(std::vector<Movie>& data, int length);

// Funckja, która jest odpowiedzialna za posortowanie wartości w kubełku.
// Wykorzystuje sortowanie przez wstawianie.
void sortBucket(std::vector<Movie>& bucket);

// Funkcja, której zadaniem jest zwrócenie największej wartość ratingu, znalezionego 
// wśród filmów.
float findMaxRating(const std::vector<Movie>& data);

#endif