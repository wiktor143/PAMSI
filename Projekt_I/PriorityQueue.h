#ifndef P_QUEUE_H
#define P_QUEUE_H
#include <iostream>
struct Node {
    std::string packet;
    unsigned int priority;
    Node *previous;
    Node *next;
};

class PriorityQueue {
   private:
    Node *head;
    Node *tail;
    void pop();
   public:
    // Konstruktor
    PriorityQueue();

    void push(unsigned int priority, const std::string &packet);

    void display();

    bool isEmpty();

    void clear();
};
#endif