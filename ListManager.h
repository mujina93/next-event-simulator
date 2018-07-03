
#ifndef LISTMANAGER_H
#define LISTMANAGER_H

class Node;
class Event;

class Dll{
public:
    Dll();
    ~Dll();
    Dll& operator=(Dll const& r) = delete;

    Node* head;
    Node* tail;

    void clear();
    Node* popN();
    Event pop();
    void scheduleN(Node* nodep);
    void schedule(Event& ev);
    void dump();
};

class Queue{
private:
    static const int MaxLength = 10000;
public:
    Queue();
    ~Queue();
    Node** data;
    int first;
    int last;

    void enqueueN(Node* nodep);
    void enqueue(Event& ev);
    Node* dequeueN();
    Event dequeue();
    void dump();
    int length();
};

class NodeManager{
public:
    static void link(Node* Lnode, Node* Rnode);
};

#endif
