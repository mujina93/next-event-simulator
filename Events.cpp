// events and node classes implementation

#include "Events.h"
#include <cstdio>
#include <iostream>

using std::cout;

Event::Event() : // null event. Equivalent to returning nullptr
    name("NULL"),from(nullptr),to(nullptr),create_time(-1),
    arrived_at(-1),leaving_at(-1),permanence_time(-1) {
}

Event::Event(string nam, Station* fr, Station* to,
            double creaT, double arrivT, double leavT, double permT) :
    name(nam),from(fr),to(to),create_time(creaT),
    arrived_at(arrivT),leaving_at(leavT),permanence_time(permT){
}

bool Event::isNull(){
    if(name=="NULL"){
        return true;
    } else {
        return false;
    }
}

void Event::dump(){
    printf("\n  EVENT:\n");
    cout <<"    name:       " << name << "\n";
    printf("    from:       %d\n", from->index);
    printf("    to:         %d\n", to->index);
    printf("    created:    %lf\n",create_time);
    printf("    arrived at: %lf\n",arrived_at);
    printf("    leaving at: %lf\n",leaving_at);
    printf("    permanence: %lf\n",permanence_time);
}

Node::Node(Event& ev) : event(ev), left(nullptr), right(nullptr) {
}

void Node::dump(){
    event.dump();
}
