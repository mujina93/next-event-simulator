// event and node classes definitions

#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include "Station.h"

using std::string;

class Event{
public:
    Event(); // Null event. Returning this is equivalent to returning nullptr
    Event(string nam, Station* fr, Station* to,
            double creaT, double arrivT, double leavT, double permT);

    string name;
    Station* from;
    Station* to;
    double create_time;
	double arrived_at;
	double leaving_at;
	double permanence_time;

	bool isNull();
	void dump();
};

class Node{
    friend class NodeManager; // NodeManager can play with Node's data
public:
    Node(Event& ev);
    Event event;
    Node* left;
    Node* right;

    void dump();
};

#endif
