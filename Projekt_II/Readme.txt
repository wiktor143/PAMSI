Istnieje możliwość kompilacji każdego pliku do postaci modułu binarego(*.o) oddzielnie 

kompilacja bucketSort.cpp do postaci modułu binarego
    w terminalu: make bucketSort.o

kompilacja readFile.cpp do postaci modułu binarego
    w terminalu: make readFile.o

kompilacja mergeSort.cpp do postaci modułu binarego
    w terminalu: make mergeSort.o

kompilacja quickSort.cpp do postaci modułu binarego
    w terminalu: make quickSort.o

kompilacja functions.cpp do postaci modułu binarego
    w terminalu: make functions.o

kompilacja programu wykonawczego i linkowanie pozostałych modułów
    w terminalu: make prog
    alternatywnie: make all
    alternatywnie: make

W sytuacji, kiedy chcemy usunąć pliki *.o i program wykonawczy "./prog"
    w terminalu: make clean

Wywołanie programu wykonawczego wygląda w następujący sposób:
    ./prog input_file_name sort_key_pos n_items algo_name [shuffle_passes] [shuffle_seed] 
istenieje możliwość wywołania programu, aby program pobrał dane z wejścia standardowego
    ./prog - sort_key_pos n_items algo_name [shuffle_passes] [shuffle_seed]
    ./prog < input_file_name

Przykładowe wywołanie programu dla pliku dane.txt zawartego w pakiecie uruchomieniowych, sort_key_pos = 3, n_items = 500, algo_name = "QUICK" 
    w terminalu: ./prog dane.csv 3 500 QUICK
Przykładowe wywołanie programu dla danych z stdin, sort_key_pos = 3, n_items = 500, algo_name = "QUICK" 
    w terminalu: ./prog - 3 500 QUICK
Przykładowe wywołanie programu dla przekierowanego pliku
    w terminalu: ./prog < dane.csv
Przykładowe wywołanie programu z dodatkowymi parametrami shuffle_passes = 2, shuffle_seed = 5
    w terminalu: ./prog dane.csv 3 500 QUICK 2 5


Istnieje możliwość testowania algorytmu dla wybranych rozmiarów elementów do sortowania za pomocą skryptu "test.sh".
Przed rozpoczęciem testowania należy przeprowadzić kompilacje programu wykonawczego zgodnie z instrukcją powyżej.

Wywołanie skryptu 
    ./test.sh - jeśli program ma nadane uprawnienia
    Dodanie uprawnień: chmod +x test.sh
bądź
    bash test.sh - jeśli program nie ma nadanych uprawnień


Skrypt stworzy plik results.txt, gdzie zapisze odpowiedź programu na wywołanie, a następnie utworzy plik times.txt, gdzie znajdować się będą
otrzymane czasy w milisekundach, wartość średnia i mediana dla kolejno przeprowadzonych testów zgodnie ze wcześniej zdefiniowaną ilością danych.