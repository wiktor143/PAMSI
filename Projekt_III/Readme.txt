Istnieje możliwość kompilacji każdego pliku do postaci modułu binarego(*.o) oddzielnie 

kompilacja checkersBoard.cpp do postaci modułu binarego
    w terminalu: make checkersBoard.o

kompilacja field.cpp do postaci modułu binarego
    w terminalu: make field.o

kompilacja gameController.cpp do postaci modułu binarego
    w terminalu: make gameController.o

kompilacja inputArgsChecker.cpp do postaci modułu binarego
    w terminalu: make inputArgsChecker.o

kompilacja player.cpp do postaci modułu binarego
    w terminalu: make player.o

kompilacja programu wykonawczego i linkowanie pozostałych modułów
    w terminalu: make prog
    alternatywnie: make all
    alternatywnie: make

W sytuacji, kiedy chcemy usunąć pliki *.o i program wykonawczy "./prog"
    w terminalu: make clean

Wywołanie programu wykonawczego wygląda w następujący sposób:
    ./prog interface turn depth [random_seed] [ip_address ip_port]

Przykładowe programu dla interfejsu "GUI", kolor programu "BLACK" i głębokości minimax 8
    ./prog GUI BLACK 8

Przykładowe programu dla interfejsu "NET", kolor programu "BLACK", głębokości minimax 8, random_seed = 150, ip_address = "localhost", ip_port - wartość zwrócona przez broker
    ./prog GUI BLACK 8 150 localhost 50771

Czasami program ma problem, aby wyrobić się w aktualnym czasie procesora dlatego proszę o zwiększenie czasu o kilka sekund.
Program miał problem z kompilacją na serwerze diablo z powodu na "undefined symbol: __xnet_connect, __xnet_socket", jednak na panamint wszystko jest w porządku.
Przypuszczam, że jest to spowodowane starą architekturą systemu.