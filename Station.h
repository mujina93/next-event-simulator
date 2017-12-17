
#ifndef STATION_H
#define STATION_H

#include <map>
#include "ListManager.h"
#include "RNG.h"

using std::map;

class Station{
public:
    enum processOutcome {RECAST, ENQUEUED};

    Station(int N, int index);
    int N;      // number clients inside
    int nin;    // number arrived clients
    int nout;   // number clients that went out
    int index;  // station's unique id
    map<Station*, double> routes; // stations where you can go and q values
    RNG selector;   // RNG which samples uniforms to decide where to route from the station

    virtual double generateTime() = 0;
    virtual Event processDeparture(Event& ev) = 0; // do things when a job goes away
    virtual Station::processOutcome processArrival(Event& ev) = 0;   // do things when a new job arrives
    Station* selectWhere();
    void setRoutes(map<Station*, double> a_routes); // add neighbour list to this station
    void reroute(Event& ev);
    void dump();
};

class ServerStation : public Station{
public:
    ServerStation(int N, int index, RNG::type ST, double* params);
    ~ServerStation();

    RNG* RandEngine;
    Queue* Q;
    int streamIndex;

    double generateTime() override;
    Event processDeparture(Event& ev) override;
    Station::processOutcome processArrival(Event& ev) override;
    void serve(Event& ev);
};

class SliceStation : public ServerStation{
public:
    SliceStation(int N, int index, RNG::type ST, double* params, double quantum);

    double quantum; // time slice

    double serve();
};

class MPD : public ServerStation{
public:
    MPD(int N, int index, RNG::type ST, double* params, int mpd);

    int MultiProgrammingDegree;

    double serve();
};

class DelayStation : public Station{
public:
    DelayStation(int N, int index, RNG::type ST, double* params);
    ~DelayStation();

    RNG* RandEngine;

    double generateTime() override;
    Event processDeparture(Event& ev) override;
    Station::processOutcome processArrival(Event& ev) override;
    double pushforward();
};


#endif // STATION_H

