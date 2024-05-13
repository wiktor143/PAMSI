#include "quickSort.h"

void quickSort(std::vector<Movie> &data, int length) {
    quickSortRecursion(data, 0, length - 1);
    return;
}

void quickSortRecursion(std::vector<Movie> &data, int lowerIndex, int upperIndex) {
    if (lowerIndex >= upperIndex) {
        return;
    }
    
    int smaller = lowerIndex;
    int greater = upperIndex;
    threeWayPartition(data, lowerIndex, upperIndex, smaller, greater);

    quickSortRecursion(data, lowerIndex, smaller - 1);
    // Prawa strona od pivota
    quickSortRecursion(data, greater + 1, upperIndex);

    return;
}

void threeWayPartition(std::vector<Movie> &data, int lowerIndex, int upperIndex, int &smaller, int &greater) {
    // Wartość pivota w sposób losowy
    srand(time(NULL));

    int pivot_index = lowerIndex + (rand() % (upperIndex - lowerIndex + 1));
    int pivot_value = data[pivot_index].rating;

    int i = lowerIndex;

    while (i <= greater) {
        if (data[i].rating < pivot_value) {
            std::swap(data[i], data[smaller]);
            i++;
            smaller++;
        } else if (data[i].rating > pivot_value) {
            std::swap(data[i], data[greater]);
            greater--;
        } else {
            i++;
        }
    }
}

