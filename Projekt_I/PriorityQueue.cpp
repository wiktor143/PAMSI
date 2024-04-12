#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : head(nullptr) {}

bool PriorityQueue::isEmpty() {
    if (head == nullptr) {  // jeżeli kolejka jest pusta
        std::cout << "Queue is empty." << std::endl;  // wyświetla komunikat
        return true;
    }
    return false;
}

void PriorityQueue::push(unsigned int priority, const std::string &packet) {
    Node *newNode = new Node;  // tworzymy nowy node
    newNode->priority = priority;
    newNode->packet = packet;
    newNode->next = nullptr;

    if (head == nullptr) {  // nie ma jeszcze nic w liście,
        head = newNode;     // nowy node jest początkiem
        return;
    }

    if (priority < head->priority) {  // wyższy priorytet niż początek? wstaw na początku
        newNode->next = head;
        head = newNode; // Nowy początek
        return;
    }

    Node *current = head;  // node do przeszukania kolejki
    while (current->next != nullptr && current->next->priority < priority) {  // przechodzimy przez kolejkę
        current = current->next;  // w poszukiwaniu odpowiedniego priorytetu
    }

    if (current->next == nullptr) {  // jeśli węzeł jest ostatni
        current->next = newNode;     // to wstawiamy na koniec
        return;
    }
    // jeżeli powyższy warunek nie został spełniony, w tym momencie dokonujemy
    // podmiany
    newNode->next = current->next;  // nowy node łączymy z następnym
    current->next = newNode;  // aktualny łączymy z nowym
}

void PriorityQueue::display() {
    if (isEmpty()) return;  // pusta to wychodzi

    Node *current = head;
    while (current != nullptr) {
        std::cout << current->packet;
        current = current->next;
    }
}

void PriorityQueue::pop() {
    if (isEmpty()) {
        std::cerr << "Error: Priority queue is empty. Cannot pop." << std::endl;
        return;
    }

    Node *temp = head;      // Store the current head node
    head = head->next;      // Move head to the next node
    delete temp;  // Delete the original head node
}

void PriorityQueue::clear() {
    while (head != nullptr) {
        pop();
    }
}