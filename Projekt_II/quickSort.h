#ifndef QUICK_SORT
#define QUICK_SORT

#include "readFile.h"
void quickSort(std::vector<Movie> &data, int length);
void quickSortRecursion(std::vector<Movie> &data, int lowerIndex, int upperIndex);
void threeWayPartition(std::vector<Movie> &data, int lowerIndex, int upperIndex, int &smaller,int &greater);

#endif