
#include "DEBUG.h"

#include "Station.h"
#include "rvgs.h"
#include <vector>
#include <map>
#include "GlobalTime.h"
#include "Events.h"
#include <cstdio>
#include <iostream>
#include <string>

using std::cout;
using std::vector;
using std::to_string;

// --- station ----
Station::Station(int N, int index) :
    N(N), nin(N), nout(0), index(index), selector(RNG::UNI,nullptr){
}

void Station::setRoutes(map<Station*, double> a_routes){
    routes = a_routes;
}

Station* Station::selectWhere(){
    // extract a probability distribution from routes map
    typedef std::map<Station*,double>::iterator mapi;
    vector<Station*> S; // stations list where is possible to go from here
    vector<double> F;   // cumulative distribution over stations S
    double cumulativeF = 0; // temporary
    for(mapi it=routes.begin(); it!=routes.end(); ++it){
        S.push_back(it->first);
        cumulativeF += it->second;
        F.push_back(cumulativeF);
    }
    // sample and choose a station. That will be your target.
    double u = selector.gen();  // uniform
    Station* chosen;
    for(unsigned i=0; i<F.size(); i++){
        if(u < F.at(i))
            chosen = S.at(i);
    }
    DD(fprintf(stderr,"(re)schedule job: from %d to %d\n",
        this->index, chosen->index));
    return chosen;
}

void Station::reroute(Event& ev){
    // select where you will send the client
    Station* where = selectWhere();
    ev.from = this;
    ev.to = where;
    ev.arrived_at = ev.leaving_at; // it will arrive at the new station as soon as it leaves this
    // ASSUMES YOU HAVE ALREADY SERVED, I.E. SET THE PERMANENCE_TIME
    ev.leaving_at = clocktime + ev.permanence_time;
}

void Station::dump(){
    printf("\n  STATION:\n");
    cout <<"    id:             " << index << "\n";
    printf("    clients inside: %d\n", N);
    printf("    arrivals:       %d\n", nin);
    printf("    departures:     %d\n", nout);
}

// --- server stations ---
ServerStation::ServerStation(int N, int index, RNG::type ST, double* params) :
    Station(N,index) {
    Q = new Queue();
    RandEngine = new RNG(ST, params);
}

ServerStation::~ServerStation(){
    delete Q;
    delete RandEngine;
}

void ServerStation::serve(Event& ev){
    // serve the event with a service time
    ev.permanence_time = generateTime();
}

Event ServerStation::processDeparture(Event& ev){
    // someone is leaving! update internal numbers
    N--;
    nout++;

    // since a job is leaving, there is free space for dequeueing
    if(N > 0){
        DR("*****BEFORE: dequeue the event:");
        DD(ev.dump());
        // dequeue
        Event ev = Q->dequeue();
        // serve
        serve(ev);
        // reroute
        reroute(ev);
        DR("*****dequeued job rerouted as:");
        DD(ev.dump());
        // recast
        return ev;
    } else {
        DR("***nothing to dequeue:");
        return Event(); // Null event. Equivalent to returning nullptr
    }
}

Station::processOutcome ServerStation::processArrival(Event& ev){
    // someone has arrived! update internal numbers
    N++;
    nin++;

    // either serve and reroute, or enqueue the job
    if(N==1){
        serve(ev);
        reroute(ev);
        DR("***job rerouted as:");
        DD(ev.dump());
        return Station::RECAST;
    } else {
        Q->enqueue(ev);
        DR("***job enqueued");
        return Station::ENQUEUED;
    }
}

double ServerStation::generateTime(){
    return RandEngine->gen();
}

// --- delay station ---
DelayStation::DelayStation(int N, int index, RNG::type ST, double* params) :
    Station(N,index){
    // initialize the internal random engine
    // (which will sample times for the clients to go away from the station)
    RandEngine = new RNG(ST, params);
}

DelayStation::~DelayStation(){
    delete RandEngine;
}

double DelayStation::generateTime(){
    return RandEngine->gen();
}

Event DelayStation::processDeparture(Event& ev){
    // someone is leaving! update internal numbers
    N--;
    nout++;

    // nothing to do, since there is no queue from which you can dequeue
    DR("***nothing to dequeue:");
    return Event(); // Null event. Equivalent to returning nullptr
}

Station::processOutcome DelayStation::processArrival(Event& ev){
    // someone has arrived! update internal numbers
    N++;
    nin++;

    // immediately recast (schedule next time the client will leave)
    ev.permanence_time = generateTime();
    reroute(ev);

    DR("***job rerouted as:");
    DD(ev.dump());

    // always recast
    return Station::RECAST;
}


// --- MPD station ---
MPD::MPD(int N, int index, RNG::type ST, double* params, int mpd) :
    ServerStation(N,index,ST,params), MultiProgrammingDegree(mpd){
}

// --- SliceStation (CPU) ---
SliceStation::SliceStation(int N, int index, RNG::type ST, double* params, double quantum) :
    ServerStation(N,index,ST,params), quantum(quantum){
}

