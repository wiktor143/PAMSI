#include "quickSort.h"

void quickSort(std::vector<Movie> &data, int length) {
    quickSortRecursion(data, 0, length - 1);
    return;
}

void quickSortRecursion(std::vector<Movie> &data, int lowerIndex, int upperIndex) {
    if (lowerIndex >= upperIndex) {
        return;  // Warunek kończący rekurencję
    }
    // Mniejsze od piwota (skrót: lower_than)
    int lt = lowerIndex;
    // Większe od piwota (skrót: greater_than)
    int gt = upperIndex;
    threeWayPartition(data, lowerIndex, upperIndex, lt, gt);

    // Lewa strona od pivota
    quickSortRecursion(data, lowerIndex, lt - 1);
    // Prawa strona od pivota
    quickSortRecursion(data, gt + 1, upperIndex);

    return;
}

void threeWayPartition(std::vector<Movie> &data, int lowerIndex, int upperIndex, int &smaller, int &greater) {
    // Wartość pivota w sposób losowy
    srand(time(NULL));

    int pivot_index = lowerIndex + (rand() % (upperIndex - lowerIndex + 1));
    int pivot_value = data[pivot_index].rating;

    // Zmienna pomocnicza do poruszania się po wektorze
    int i = lowerIndex;

    // Jeśli wartość i jest mniejsza bądź równa wartośći greater znaczy to, że sortowanie dobiegło końca
    while (i <= greater) {
        // Mniejszy od pivota przesuń na początek(na lewo od granicy)
        if (data[i].rating < pivot_value) {
            std::swap(data[i], data[smaller]);
            i++;
            smaller++;
            // Większy od pivota przesuń na koniec(na prawo od granicy)
        } else if (data[i].rating > pivot_value) {
            std::swap(data[i], data[greater]);
            // Jedna wartość w lewo od końca(mniej elementów większych od pivota)
            greater--;
        } else {
            // Jeśli wartość jest równa wartości pivota, idz do kolejnego elementu(nie zamieniaj miejscami)
            i++;
        }
    }
}
