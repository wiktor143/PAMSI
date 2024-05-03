#!/bin/bash

# Początkowy rozmiar wiadomości
start_message_size=5000
# Końcowy rozmiar wiadomości
end_message_size=100000
# Krok zwiększania rozmiaru wiadomości
step=25000

# Usunięcie poprzednich wyników z plików
>results.txt
>times.txt

# Pętla testująca program dla różnych rozmiarów wiadomości
for ((message_size = $start_message_size; message_size <= $end_message_size; message_size += $step)); do
    echo "Test dla rozmiaru wiadomości: $message_size B"
    ./prog tekst.txt 0 $message_size 100 >>results.txt
    # Pobranie ostatniej linii z pliku wynikowego i wyświetlenie
    last_line=$(tail -n 1 results.txt)
    echo "$last_line" >>times.txt
done
