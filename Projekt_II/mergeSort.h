#ifndef MERGE_SORT
#define MERGE_SORT

#include"readFile.h"

// Funkcja jest interfejsem dla algorytmu sortowania przez scalanie.
void mergeSort(std::vector<Movie> &data, int length);

// Funkcja odpowiada za dzielenie wektora danych data na dwie połówki, aż do uzyskania 
// tablic jednoelementowych. Wywołuje ona siebie rekurencyjnie, aby podzielić dane na coraz
// mniejsze fragmenty, a następnie łączy wyniki sortowania za pomocą funkcji merge.
void mergeDivide(std::vector<Movie> &data, int leftIndex, int rightIndex);

// Funkcja scalająca jest odpowiedzialna za scalanie dwóch posortowanych połówek wektora danych data. 
// Tworzy ona dwie tymczasowe tablice (tempLeft i tempRight), do których kopiowane są odpowiednie fragmenty danych. 
// Następnie porównuje ona elementy z obu tablic tymczasowych i umieszcza je w odpowiedniej kolejności w oryginalnym wektorze danych 
void merge(std::vector<Movie> &data, int leftIndex,int middleIndex, int rightIndex);

#endif