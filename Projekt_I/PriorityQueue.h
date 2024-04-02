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

   public:
    PriorityQueue();
    void push(unsigned int priority, const std::string &packet);
    void printQueue();
    bool isEmpty();

};
#endif