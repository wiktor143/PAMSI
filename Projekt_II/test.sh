#!/bin/bash

# Nazwa pliku danych
filename="dane.csv"

# Numer kolumny
column=3

# Algorytm sortowania
algorithm="BUCKET"

# Rozmiary danych do sortowania
data_sizes=(10000 50000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000 1010191)

# Usunięcie poprzednich wyników z plików
>results.txt
>times.txt

# Wykonanie testów dla każdego rozmiaru danych
for size in "${data_sizes[@]}"; do
    echo "Testowanie dla rozmiaru danych: $size"
    ./prog "$filename" "$column" "$size" "$algorithm" >>results.txt
    # Zapisanie ostatnich trzech wierszy do pliku
    last_line=$(tail -n 3 results.txt)
    echo "Dla: $size" >>times.txt
    echo "$last_line" >>times.txt
    echo " " >>times.txt
done
