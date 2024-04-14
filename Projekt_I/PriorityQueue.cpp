#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : head(nullptr) {}

bool PriorityQueue::isEmpty() const {
    if (head == nullptr) {                            // Jeżeli kolejka jest pusta
        std::cout << "Queue is empty." << std::endl;  // Wyświetla komunikat
        return true;
    }
    return false;
}

void PriorityQueue::push(unsigned int priority, const std::string &packet) {
    Node *newNode = new Node;      // Tworzymy nowy node
    newNode->priority = priority;  // Ustawiamy priorytet
    newNode->packet = packet;      // Przypisujemy pakiet
    newNode->next = nullptr;       // Ustawiamy wskaźnik następny na nullptr

    if (head == nullptr) {  // Nie ma jeszcze nic w liście
        head = newNode;     // Nowy node jest początkiem listy
        return;
    }

    if (priority < head->priority) {  // Wyższy priorytet niż początek? Wstaw na początku
        newNode->next = head;
        head = newNode;  // Nowy początek listy
        return;
    }

    Node *current = head;  // Node do przeszukania kolejki
    while (current->next != nullptr && current->next->priority < priority) {  // przechodzimy przez kolejkę
        current = current->next;                  // w poszukiwaniu odpowiedniego priorytetu
    }

    if (current->next == nullptr) {  // Jeśli węzeł jest ostatni
        current->next = newNode;     // To wstawiamy na koniec
        return;
    }
    // Jeżeli powyższy warunek nie został spełniony, w tym momencie dokonujemy podmiany
    newNode->next = current->next;  // Nowy node łączymy z następnym
    current->next = newNode;        // Aktualny łączymy z nowym
}

void PriorityQueue::display() {
    if (isEmpty()) return;  // Kolejka jest pusta to wychodzi

    Node *current = head;             // Wskaźnik pomocniczy 
    while (current != nullptr) {      // Przechodzimy przez całą listę
        std::cout << current->packet; // Wyświetlamy zawartość pakietu
        current = current->next;      // Przechodzimy do następnego node'a
    }
}

void PriorityQueue::pop() {
    if (isEmpty()) { // Kolejka jest pusta to wychodzi
        std::cerr << "Error: Priority queue is empty. Cannot pop." << std::endl;
        return;
    }

    Node *temp = head;  // Przetrzymujemy wskaźnik na początek listy
    head = head->next;  // Przesuwamy wskaźnik na następny node
    delete temp;        // Zwalniamy pamięć dla starej głowy
}

void PriorityQueue::clear() {
    while (head != nullptr) { // Przechodzimy przez całą listę usuwając kolejne elementy
        pop();                // Usuwamy zgodnie z malejącym priorytetem 
    }
}