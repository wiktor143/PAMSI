#include "bucketSort.h"

void sortBucket(std::vector<Movie>& bucket) {
    int length = static_cast<int>(bucket.size());
    // Start pętli od drugiego elementu, ponieważ pierwszy traktujemy jako już posortowany
    for (int i = 1; i < length; ++i) {
        // Wartość aktualnego elementu
        Movie key = bucket[i];
        // Indeks elementu wcześniejszego
        int j = i - 1;
        // Pętla dopóki indeks j nie będzie mniejszy od zera i wartość
        // kubełka pod j jest większa od ratingu
        while (j >= 0 && bucket[j].rating > key.rating) {
            // Zamiana elementów
            bucket[j + 1] = bucket[j];
            // Przechodzimy tak długo, aż rating pod j będzie mniejszy bądź równy
            // wartości elementu "key"
            j = j - 1;
        }
        // Wstawiamy wartość "key" na odpowiednią pozycję, czyli zaraz za ostanim przesuniętym
        // elementem
        bucket[j + 1] = key;
    }
}

void bucketSort(std::vector<Movie>& data, int length) {
    // Liczba kubełków odpowiada liczbie możliwych ocen [0 do maxRating]
    int num_buckets = findMaxRating(data) + 1;

    // Stworzenie wektora kubełków
    std::vector<std::vector<Movie>> buckets(num_buckets);

    // Wstawianie filmów do odpowiednich kubełków, dla wartości int na tym etapie
    // rating jest już posortowany.
    for (int i = 0; i < length; ++i) {
        buckets[data[i].rating].push_back(data[i]);
    }

    // Sortuj filmy wewnątrz każdego kubełka (sortowanie przez wstawianie), jeżeli będziemy mięc
    // do czynienia z ratingiem typu float np. 1.1. Dla wartości int takich jak w pliku "dane.csv"
    // sortowanie przez wstawianie się nie odbędzie(dane już są posortowane).
    int index = 0;
    for (int i = 0; i < static_cast<int>(buckets.size()); ++i) {
        sortBucket(buckets[i]);
        for (int j = 0; j < static_cast<int>(buckets[i].size()); ++j) {
            // Przepisanie posortowanych wartości do oryginalnego wektora
            data[index++] = buckets[i][j];
        }
    }
}

float findMaxRating(const std::vector<Movie>& data) {
    float maxRating = 0;
    for (const auto& movie : data) {
        maxRating = std::max(maxRating, movie.rating);
    }
    return maxRating;
}