
#include "DEBUG.h"

#include "Station.h"
#include "System.h"
#include "rvgs.h"
#include <vector>
#include <map>
#include "GlobalTime.h"
#include "Events.h"
#include <cstdio>
#include <iostream>
#include <string>
#include "Observer.h"

using std::cout;
using std::cerr;
using std::vector;
using std::to_string;

// --- station ----
Station::Station(int N, int index) :
    N(N), nin(N), nout(0), index(index), selector(RNG::UNI,nullptr),
    MVAtype(Station::LI){
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
        ///DD(fprintf(stderr,"fr: %d, to: %d, p: %lf\n",this->index,it->first->index,cumulativeF));
    }
    // sample and choose a station. That will be your target.
    double u = selector.gen();  // uniform
    Station* chosen;
    for(unsigned i=F.size(); i --> 0; ){
        if(u < F.at(i)){
            ///DD(fprintf(stderr,"fr: %d, u: %lf, p: %lf, at: %d\n",this->index,u,F.at(i),S.at(i)->index));
            chosen = S.at(i);
        }
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

bool Station::isExp(){
    if(RandEngine->typ == RNG::EXP){
        return true;
    } else {
        return false;
    }
}

Station::StationType Station::getType(){
    return MVAtype;
}

double Station::getTypicalTime(){
    return RandEngine->getTypicalTime();
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
    ///DD(fprintf(stderr,"generated service time: %lf\n",ev.permanence_time));
}

Event ServerStation::processDeparture(Event& ev){
    // someone is leaving! update internal numbers
    N--;
    nout++;

    // since a job is leaving, there is free space for dequeueing
    if(N > 0){
        // dequeue
        Event dev = Q->dequeue();
        DR("*****BEFORE: dequeue the event:");
        DD(dev.dump());
        // serve
        serve(dev);
        // reroute
        reroute(dev);
        DR("*****dequeued job rerouted as:");
        DD(dev.dump());
        // recast
        return dev;
    } else {
        DR("***nothing to dequeue:");
        return Event(); // Null event. Equivalent to returning nullptr
    }
}

Event ServerStation::processArrival(Event& ev){
    // someone has arrived! update internal numbers
    N++;
    nin++;

    // either serve and reroute, or enqueue the job
    if(N==1){
        serve(ev);
        reroute(ev);
        DR("***job rerouted as:");
        DD(ev.dump());
        return ev;
    } else {
        Q->enqueue(ev);
        DR("***job enqueued");
        return Event();
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
    // override default MVAtype 'LI'
    MVAtype = Station::D;
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

Event DelayStation::processArrival(Event& ev){
    // someone has arrived! update internal numbers
    N++;
    nin++;

    // immediately recast (schedule next time the client will leave)
    ev.permanence_time = generateTime();
    reroute(ev);

    DR("***job rerouted as:");
    DD(ev.dump());

    // always recast
    return ev;
}


// --- MPD station ---
MPD::MPD(int N, int index, int mpd) :
    ServerStation(N,index,RNG::INST,nullptr), MultiProgrammingDegree(mpd),
    underControl(){
}

Event MPD::processDeparture(Event& ev){
    // someone is leaving! update internal numbers
    N--;
    nout++;

    DR("***Simply processing a departure from MPD");
    return Event();
}

Event MPD::processArrival(Event& ev){
    // someone has arrived! update internal numbers
    N++;
    nin++;

    // if the part of the system under control has space, recast immediately
    if(N == 1 && populosity() < MultiProgrammingDegree){
        serve(ev);
        reroute(ev);

        DR("***job rerouted as:");
        DD(ev.dump());
        return ev;
    } else {
        // else, enqueue the job
        Q->enqueue(ev);

        DR("***job stopped by MPD and enqueued");
        return Event();  // return nothing
    }
}

void MPD::update(){
    DER("Length of queue at MPD reserve: %d\n",Q->length());
    // if there is someone in the MPD queue => dequeue and send it
    if(Q->length()>0 && populosity()<MultiProgrammingDegree){
        Event dev = Q->dequeue();
        serve(dev);
        reroute(dev);

        // here we force from the Observer (MPD)
        // the Subject (system) to do something, as effect of
        // update(): to schedule the dequeued job
        System* system = static_cast<System*>(watched);
        system->schedule(dev);

        DR("***INSTANT: job dequeued and scheduled by MPD as:");
        DD(dev.dump());
    }
}

int MPD::populosity(){
    typedef std::set<Station*>::iterator ssi;
    int sum = 0;
    for (ssi it = underControl.begin(); it != underControl.end(); ++it){
        sum += (*it)->N;
    }
    //DD(fprintf(stderr,"Populosity in active system: %d\n",sum));
    return sum;
}

void MPD::watch(System* Sys){
    DR("observer: started watching system...");
    Observer::watch(static_cast<Subject*>(Sys));
}

void MPD::addUnderControl(Station* S){
    DR("observer: station added under control");
    underControl.insert(S);
}

// --- SliceStation (CPU) ---
SliceStation::SliceStation(int N, int index, RNG::type ST, double* params, double quantum) :
    ServerStation(N,index,ST,params), quantum(quantum), slicedJobs(){
}

Event SliceStation::processDeparture(Event& ev){
    // someone is leaving! update internal numbers
    N--;
    nout++;

    // since a job is leaving, there is free space for dequeueing
    // process another event
    if(N > 0){
        // dequeue
        Event dev = Q->dequeue();
        DR("*****dequeue the event:");
        DD(dev.dump());
        // serve (either assign S to new event,
        // or subtract quantum to sliced event which is here again)
        serve(dev);
        // reroute
        if(dev.permanence_time > quantum){
            // if there is still work to do, this event will be sliced
            sendBack(dev); // Change this event: from this -> to this

            // register it as sliced
            slicedJobs.insert(dev.name);

            DR("*****dequeued job and sent back as:");
            DD(dev.dump());
        } else {
            // if you can finish the work, send the completed job out
            reroute(dev);
            // the job is not sliced anymore
            slicedJobs.erase(dev.name);

            DR("*****dequeued job and rerouted as:");
            DD(dev.dump());
        }
        // expose the sent-back or rerouted event
        return dev;
    } else {
        // else, that job was the only one
        DR("***nothing to dequeue:");
        return Event(); // Null event. Equivalent to returning nullptr
    }
}

Event SliceStation::processArrival(Event& ev){
    // someone has arrived! update internal numbers
    N++;
    nin++;

    // process the job
    if(N==1){
        // serve (either assign S to new event,
        // or subtract quantum to sliced event which is here again)
        serve(ev);
        // reroute
        if(ev.permanence_time > quantum){
            // if there is still work to do, this event will be sliced
            sendBack(ev); // Change this event: from this -> to this

            // register it as sliced
            slicedJobs.insert(ev.name);

            DR("***job sent back as:");
            DD(ev.dump());
        } else {
            // if you can finish the work, send the completed job out
            reroute(ev);
            // the job is not sliced anymore
            slicedJobs.erase(ev.name);

            DR("***job and rerouted as:");
            DD(ev.dump());
        }
        // expose the sent-back or rerouted event
        return ev;
    } else {
        Q->enqueue(ev);
        DR("***job enqueued");
        DD(ev.dump());

        return Event();
    }
}

void SliceStation::serve(Event& ev){
    if(slicedJobs.find(ev.name) == slicedJobs.end()){
        // if this is a fresh new job, serve
        ev.permanence_time = generateTime();
        DD(fprintf(stderr,"*****new service assigned: %lf\n",ev.permanence_time));
    } else {
        // if instead this job was already postponed, do nothing
    }
}

void SliceStation::sendBack(Event& ev){
    // reroute back the job to the SliceStation
    ev.from = this;
    ev.to = this;
    // DOES NOT MODIFY arrived_at
    ev.permanence_time -= quantum;
    DR("*****job sliced:");
    ev.leaving_at = clocktime + quantum; // only a quantum of time has passed
}

