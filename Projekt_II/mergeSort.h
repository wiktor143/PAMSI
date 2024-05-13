#ifndef MERGE_SORT
#define MERGE_SORT

#include"readFile.h"

void mergeSort(std::vector<Movie> &data, int length);
void mergeDivide(std::vector<Movie> &data, int leftIndex, int rightIndex);
void merge(std::vector<Movie> &data, int leftIndex,int middleIndex, int rightIndex);

#endif