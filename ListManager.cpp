
#define DEBLIST 0

#include "DEBUG.h"
#include <cstdio>
#include "ListManager.h"
#include "Events.h"

Dll::Dll() : head(nullptr), tail(nullptr) {
}

Dll::~Dll(){
    // clean doubly linked list
    // in case all the nodes were instantiated dynamically
    Node* probe = head;
    if(probe!=nullptr){
        while(probe != tail){
            // go on one step
            probe = probe->right;
            // clean
            delete probe->left;
        }
        // free tail
        delete probe;
    }
    return;
}

void Dll::clear(){
    // clean doubly linked list
    Node* probe = head;
    if(probe!=nullptr){
        while(probe != tail){
            // go on one step
            probe = probe->right;
            // clean
            delete probe->left;
        }
        // free tail
        delete probe;
    }

    // re-initialize head and tail
    head->right = nullptr;
    head = nullptr;
    tail = nullptr;
}

Node* Dll::popN(){
    // if list becomes empty, set tail to nullptr
    if(head->right==nullptr){
        tail = nullptr;
    }
    // return head and update head pointer
    Node* to_be_returned = head;


    head = head->right;
    return to_be_returned;
}

Event Dll::pop(){
    Node* nodep = popN();
    Event ev = nodep->event;
    // removes the wrap and returns the event
    delete nodep;
    return ev;
}

void Dll::scheduleN(Node* nodep){
#if DEBLIST==1
    printf("HEAD  %p\n",head);
#endif
    double when = nodep->event.leaving_at;
    double t;

    // TRAVERSE AND INSERT

    // probe node used for traversal
    Node* probe = head;

    // if FEL empty -> this is the only event
    if(probe==nullptr){
    #if DEBLIST==1
        printf("EMPTY FEL\n");
    #endif
        head = nodep;
        tail = nodep;
        nodep->left = nullptr;
        nodep->right = nullptr;
    }
    // if it is not empty...
    else{
        t = probe->event.leaving_at;
        #if DEBLIST==1
        printf("NOT EMPTY. t: %lf w: %lf\n",t,when);
        #endif
        // if this event is earlier than any other
        // -> set this as new head (not true in case of ties)
        if(when < t){
        #if DEBLIST==1
            printf("NEW HEAD when: %lf\n",when);
        #endif
            NodeManager::link(nodep, head);
            nodep->left = nullptr;
            head = nodep;
        }
        // otherwise, traverse and find where to insert
        else{
            // as long as probe->right is not the tail, you can go on and
            // look for some node which will occur later than nodep.
            // If you find a place where you can insert nodep, break the loop.
            while(probe != tail){
                // go on one step
                probe = probe->right;
                t = probe->event.leaving_at;
                #if DEBLIST==1
                printf("EXPLORING: t: %lf\n",t);
                #endif
                // INSERT!
                if(when < t){
                #if DEBLIST==1
                    printf("INSERT w %lf < t %lf\n",when,t);
                #endif
                    NodeManager::link(probe->left, nodep);
                    NodeManager::link(nodep, probe);
                    break;
                }
            }
            // if you when through the list until probe->right == tail, and you
            // did not find a place where to insert nodep yet, then insert
            // it at the end (either before or after the tail, depending on leaving_at)
            if(when > tail->event.leaving_at){
            #if DEBLIST==1
                printf("INSERT AS TAIL\n");
            #endif
                NodeManager::link(tail, nodep);
                nodep->right = nullptr;
                tail = nodep;
            }
        }
    }
#if DEBLIST==1
    printf("scheduling\n");
    print_node(nodep);
#endif
    return;
}

void Dll::schedule(Event& ev){
    // wraps the event with Node and schedule
    Node* nodep = new Node(ev);
    scheduleN(nodep);
}

void Dll::dump(){
    printf("\nDOUBLY LINKED LIST\n");
    // probe node used for traversal
    Node* probe = head;

    // if List is empty -> print nothing
    if(probe==nullptr){
        printf("The list is empty\n");
    }
    // otherwise, traverse and print
    else{
        while(probe != tail){
            // prints
            probe->dump();
            // go on one step
            probe = probe->right;
        }
        // prints tail
        probe->dump();
    }
}

// --- Queue ---

void Queue::dump(){
    printf("\nQUEUE\n");
    if(first==last){
        printf("    empty\n");
    }
    for(int i=first; i<last; i++){
        data[i]->dump();
    }
    printf("\n");
}

Queue::Queue() : first(0), last(0) {
    data = new Node*[MaxLength];
}

Queue::~Queue(){
    delete [] data;
}

void Queue::enqueueN(Node* nodep){
    data[last] = nodep;
    last = (last + 1) % MaxLength;
    return;
}

void Queue::enqueue(Event& ev){
    // wraps event with Node first
    Node* nodep = new Node(ev);
    enqueueN(nodep);
}

Node* Queue::dequeueN(){
    Node* to_be_returned = data[first];
    first = (first + 1) % MaxLength;
    return to_be_returned;
}

Event Queue::dequeue(){
    // removes the wrap and returns just the event
    Node* nodep = dequeueN();
    Event ev = nodep->event;
    delete nodep;
    return ev;
}

int Queue::length(){
    return ((last - first)>=0) ? (last - first) : (MaxLength + last - first);
}

// --- NodeManager ---
void NodeManager::link(Node* Lnode, Node* Rnode){
    Rnode->left = Lnode;
    Lnode->right = Rnode;
    return;
}


