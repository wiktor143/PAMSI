#ifndef QUICK_SORT
#define QUICK_SORT

#include "readFile.h"

// Funkcja jest interfejsem dla algorytmu sortowania szybkiego. Wywołuje ona funkcję quickSortRecursion, 
// aby rozpocząć proces sortowania.
void quickSort(std::vector<Movie> &data, int length);

// Funkcja ta jest częścią rekurencyjną algorytmu sortowania szybkiego. Dzieli ona wektor danych 
// data na trzy części: elementy mniejsze od pivota, elementy równe pivotowi oraz elementy większe od pivota. 
// Następnie rekurencyjnie sortuje ona lewą część (mniejsze od pivota) i prawą część (większe od pivota) wektora.
void quickSortRecursion(std::vector<Movie> &data, int lowerIndex, int upperIndex);

// Ta funkcja wykonuje trzykierunkowy podział danych (three-way partitioning). 
// Wybiera losowy element jako pivot, a następnie porównuje każdy element z pivotem, dzieląc dane na trzy części: 
// elementy mniejsze od pivota, elementy równe pivotowi oraz elementy większe od pivota. Parametry smaller i greater są referencjami 
// do zmiennych pomocniczych, które przechowują granice obszarów danych mniejszych i większych od pivota.
void threeWayPartition(std::vector<Movie> &data, int lowerIndex, int upperIndex, int &smaller,int &greater);

#endif