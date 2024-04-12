#ifndef P_QUEUE_H
#define P_QUEUE_H
#include <iostream>

// Struktura jednego node'a
struct Node {
    std::string packet;
    unsigned int priority;
    Node *next;
};

class PriorityQueue {
   private:
    Node *head;

    // Funkcja służąca do usunięcia node'a o największym(w naszym przypadku
    // pierwszego) priorytecie.
    void pop();

   public:
    // Konstruktor
    PriorityQueue();

    // Funckja służąca do dodania kolejnego node'a do kolejki priorytetowej
    // oraz ustawienia go zgodnie z priorytetem.
    void push(unsigned int priority, const std::string &packet);
    // Funkcja służąca do wyświetlenia stanu kolejki priorytetowej.
    void display();

    // Funkcja służąca do sprawdzenie czy kolejka priorytetowa jest pusta.
    bool isEmpty();

    // Funckja służąca do usunięcia całej kolejki priorytetowej.
    void clear();
};
#endif