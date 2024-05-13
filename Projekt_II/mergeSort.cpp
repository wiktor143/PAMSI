#include "mergeSort.h"

void mergeSort(std::vector<Movie> &data, int length) {
    mergeDivide(data, 0, length - 1);
    return;
}

void mergeDivide(std::vector<Movie> &data, int leftIndex, int rightIndex) {
    // Dopóki lewa strona jest mniejsza od prawej kontynuuj rekurencje
    if (leftIndex >= rightIndex) {
        return;
    }

    // Wartość środkowego indeksu w tablicy
    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

    // Rekurencyjne rozbicie na dwie podtablice aż do uzyskania tablic jednoelementowych
    mergeDivide(data, leftIndex, middleIndex);
    mergeDivide(data, middleIndex + 1, rightIndex);

    merge(data, leftIndex, middleIndex, rightIndex);
    return;
}

void merge(std::vector<Movie> &data, int leftIndex, int middleIndex, int rightIndex) {
    // Długość lewej podtablicy
    int subLeftLength = middleIndex - leftIndex + 1;
    // Długość prawej podtablicy
    int subRightLength = rightIndex - middleIndex;
    // Zmienne do poruszania się po podtablicy: i = lewa, j = prawa i k = złączona
    int i, j, k;

    // Wektory do chwilowego przechowania lewej i prawej strony wektora "data"
    std::vector<Movie> tempLeft;
    std::vector<Movie> tempRight;

    for (int i = 0; i < subLeftLength; i++) {
        // Kopiujemy lewą strone wekotra "data"
        tempLeft.push_back(data[leftIndex + i]);
    }

    for (int i = 0; i < subRightLength; i++) {
        // Kopiujemy prawą strone wekotra "data"
        tempRight.push_back(data[middleIndex + 1 + i]);
    }

    // Pętla startuje od lewego indeksu aż do końca czyli prawego indeksu
    for (i = 0, j = 0, k = leftIndex; k <= rightIndex; k++) {
        // Jeśli indeks lewej podtablicy nie przekroczył długości i indeks prawej podtablicy jest
        // większy niż długość przypisz element z lewej pod tablicy do złączonej. Albo rating lewej
        // i prawej są porównywane i wartość lewej jest mniejsza przypisz wartość lewej
        if ((i < subLeftLength) &&
            (j >= subRightLength || tempLeft[i].rating <= tempRight[j].rating)) {
            data[k] = tempLeft[i];
            i++;
            // Jeśli powyższy warunek nie zostanie spełniony, przypisz wartość prawej pod tablicy do
            // tablicy złączonej
        } else {
            data[k] = tempRight[j];
            j++;
        }
    }
    return;
}