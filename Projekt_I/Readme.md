Istnieje możliwość kompilacji każdego pliku do postaci modułu binarego(*.o) oddzielnie 

kompilacja PriorityQueue.cpp do postaci modułu binarego
    w terminalu: make PriorityQueue.o

kompilacja ReadFile.cpp do postaci modułu binarego
    w terminalu: make ReadFile.o

kompilacja Transfer.cpp do postaci modułu binarego
    w terminalu: make Transfer.o

kompilacja driver.cpp do postaci modułu binarego
    w terminalu: make driver.o

kompilacja programu wykonawczego i linkowanie pozostałych modułów
    w terminalu: make prog
    alternatywnie: make all
    alternatywnie: make

W sytuacji, kiedy chcemy usunąć pliki *.o i program wykonawczy "./prog"
    w terminalu: make clean

Wywołanie programu wykonawczego wygląda w następujący sposób:
    ./prog file_name file_offset message_size packet_size 
istenieje możliwość wywołania programu z dodatkowym parametrem '1', wtedy zobaczymy "potasowaną" wiadomość przed wysłaniem
    ./prog file_name file_offset message_size packet_size 1

Przykładowe wywołanie programu dla pliku tekst.txt zawartego w pakiecie uruchomieniowych, offsetu 0, rozmiaru wiadomości 1 kB, rozmiaru pakietu 100 B 
    w terminalu: ./prog tekst.txt 0 1000 100
Przykładowe wywołanie programu z dodatkowym parametrem
    w terminalu: ./prog tekst.txt 0 1000 100 1

Offset przyjmuje wartości od <0;2147483648), jest to spowodowane rozmiarem int'a
Dodatkowo offset może zostać wylosowany z przedziału <0;100000) wystarczy za offset podać wartość '-1'
    w terminalu: ./prog tekst.txt -1 1000 100

Istnieje możliwość testowania algorytmu dla wybranych rozmiarów wiadomości za pomocą skryptu "test.sh".
Przed rozpoczęciem testowania należy przeprowadzić kompilacje programu wykonawczego zgodnie z instrukcją powyżej, następnie
wybrać zakres rozmiaru wiadomości do testów <start_message_size;end_message_size> i skok "step".
Skrypt stworzy plik results.txt, gdzie zapisze odpowiedź programu na wywołanie, a następnie utworzy plik times.txt, gdzie znajdować się będą
otrzymane czasy w milisekundach dla kolejno przeprowadzonych testów zgodnie ze wcześniej zdefiniowanym rozmiarem.
