
#ifndef STATION_H
#define STATION_H

#include <map>
#include "ListManager.h"
#include "RNG.h"
#include <set>
#include <string>
#include "Observer.h"
#include "Subject.h"

using std::set;
using std::string;
using std::map;
class System;

class Station{
public:
    enum StationType { D, LI }; // delay or load independent. Default: LI. Delay is: D.

    Station(int N, int index);
    int N;      // number clients inside
    int nin;    // number arrived clients
    int nout;   // number clients that went out
    int index;  // station's unique id
    map<Station*, double> routes; // stations where you can go and q values
    RNG selector;   // RNG which samples uniforms to decide where to route from the station
    RNG* RandEngine; // RNG that generates random (service) times typical for this station
    StationType MVAtype;

    virtual double generateTime() = 0;              // this station's way of generating a random time (usually service time)
    virtual Event processDeparture(Event& ev) = 0; // do things when a job goes away
    virtual Event processArrival(Event& ev) = 0;   // do things when a new job arrives
    Station* selectWhere();                         // select a station where to go from here
    void setRoutes(map<Station*, double> a_routes); // add neighbour list to this station
    void reroute(Event& ev);                        // set the given event from here to another station
    void dump();                                    // prints description
    bool isExp();                                   // true if this station has an exponential engine
    StationType getType();                          // type for MVA analysis
    double getTypicalTime();                        // gets mean time from RNG
};

class ServerStation : public Station{
public:
    ServerStation(int N, int index, RNG::type ST, double* params);
    ~ServerStation();

    Queue* Q;
    int streamIndex;

    double generateTime() override;
    virtual Event processDeparture(Event& ev) override;
    virtual Event processArrival(Event& ev) override;
    virtual void serve(Event& ev);
};

class SliceStation : public ServerStation{
public:
    SliceStation(int N, int index, RNG::type ST, double* params, double quantum);

    double quantum;             // time slice
    set<string> slicedJobs;  // names of postponed jobs

    Event processDeparture(Event& ev) override;
    Event processArrival(Event& ev) override;
    void serve(Event& ev) override;
    void sendBack(Event& ev);
};

class MPD : public ServerStation, public Observer{
public:
    MPD(int N, int index, int mpd);

    int MultiProgrammingDegree; // maximum number of clients in the system under control
    set<Station*> underControl; // part of the system under control

    void watch(System* Sys); // watch a system for notifications. overLOAD: original one is watch(Subject* S)
    void update() override;  // do things when notified by the watched system
    Event processDeparture(Event& ev) override;
    Event processArrival(Event& ev) override;
    void addUnderControl(Station* S); // adds a station under control
    int populosity(); // counts the number of clients in the part of the system under control
};

class DelayStation : public Station{
public:
    DelayStation(int N, int index, RNG::type ST, double* params);
    ~DelayStation();

    double generateTime() override;
    Event processDeparture(Event& ev) override;
    Event processArrival(Event& ev) override;
};


#endif // STATION_H

