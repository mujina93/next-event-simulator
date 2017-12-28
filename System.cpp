
#include "DEBUG.h"

#include "System.h"
#include <cstdio>
#include <string>
#include "GlobalTime.h"
#include "Events.h"
#include <iostream>
#include <exception>
#include "Station.h"
#include <typeinfo>
#include <algorithm>

using std::vector;
using std::string;
using std::to_string;

System::System(vector<Station*> a_stations, double MaxTime, int MaxCycles) :
    initial_state(), MarkovStations(),
    stations(a_stations), FEL(), reg(0),
    Max_Time(MaxTime), job_number(0), first_event(false),
    Max_Cycles(MaxCycles){
    DR("Creating the system ---");
    // bootstrap: generate the first events for all stations which have clients
    typedef vector<Station*>::iterator vsi;
    for(vsi it=stations.begin(); it!=stations.end(); ++it){
        DR("--- At station: ");
        DD((*it)->dump());
        for(int i=0; i<((*it)->N); i++){
            // initializing with the first events
            generate_event(*it);
            // registering the initial state
            // (could be useful when looking for regeneration points)
            initial_state.push_back((*it)->N);
        }
        // remember which stations have NegExp service times
        // (useful when looking for regeneration points)
        if((*it)->isExp()){
            MarkovStations.push_back((*it));
        }
    }
    DR("--- System created");
    #if DEBUG==1
        for(vsi it=MarkovStations.begin(); it!=MarkovStations.end(); ++it){
            fprintf(stderr, "markov station: %d\n",(*it)->index);
        }
    #endif
}

Station* System::operator[](int i){
    return stations[i];
}

vector<int> System::get_state(){
    vector<int> vec;
    typedef vector<Station*>::iterator vsi;
    for(vsi it=stations.begin(); it!=stations.end(); ++it){
        vec.push_back((*it)->N);
    }
    return vec;
}

bool System::engine(){
    DR("\n+++++++++++++engine++++++++++++:");

    // pop event
    Event pop_ev = FEL.pop();

    // update clock
    double oldtime = clocktime;
    clocktime = pop_ev.leaving_at;

    // notify WalkStatBalls
    notifyEvent(pop_ev);

    // if you hit enough cycles, stop
    if(hitRegeneration(pop_ev) && reg==Max_Cycles){
        DER("reached %d regeneration cycles\nEND OF SIMULATION",Max_Cycles);
        return true;  // do halt!
    }

    // process event
    DR("Processing the event");
    DD(pop_ev.dump());

    // the job is leaving StazFrom => so it frees up space for a
    // dequeue (if there are pending jobs in StazFrom)
    Station* StazFrom = pop_ev.from;
    DD(fprintf(stderr,"DEP) Staton %d: ",StazFrom->index));
    Event dequeued = StazFrom->processDeparture(pop_ev);
    if( !dequeued.isNull() ){
        schedule(dequeued);
    } else {
        // processDeparture returned no useful event. Nothing to do
    }

    // the job arrives to StazTo. StazTo processes now the event
    // it can serve and recast it, or it can enqueue it.
    Station* StazTo = pop_ev.to;
    DD(fprintf(stderr,"ARR) Station %d: ",StazTo->index));
    Event new_ev = StazTo->processArrival(pop_ev);
    if( !new_ev.isNull() ){
        // A new event was cast. Insert into FEL
        schedule(pop_ev);
    } else {
        // pop_ev was enqueued. Nothing to do.
    }

    // notify the Observers (if any)
    // (in our case, notify the MPD station that could want
    // to dequeue and recast and schedule immediately a job)
    notify();

    // if simulation is too long, abort
    if(clocktime > Max_Time){
        fprintf(stderr, "Simulation took too much!\nAborted\n");
        return true;  // do halt!
    } else {
        return false; // don't halt!
    }
}

bool System::hitRegeneration(Event& ev){
    bool hitReg = false;
    // everything back to initial state. New event from then
    if(get_state()==initial_state){
        DR("Hit regeneration (returned to initial state)");
        hitReg = true;
    }
    // a valid regeneration point is an arrival to a Markov station (one with NegExp service times)
    else if(std::find(MarkovStations.begin(),MarkovStations.end(),ev.to)!=MarkovStations.end()){
        // MarkovStations contains the station where ev is heading
        DR("Hit regeneration (arrival to Markov station)");
        hitReg = true;
    }
    // if you hit regeneration, reg++ and notify WalkStatBalls
    if(hitReg == true){
        reg++;
        notifyRegeneration();
    }
    // else
    return hitReg;
}

void System::simulate(){
    bool halt = false;
    while(!halt){
        halt = engine();
    }
}

void System::generate_event(Station* fr){
    // new event's parameters
    string evname = "J" + to_string(job_number++);
    double permanence;
    if(!first_event){
        // first event starts at 0 artificially
        permanence = 0;
        first_event = true;
    } else {
        // otherwise, serve normally
        permanence = fr->generateTime();
    }
    // pick a suitable arrival station
    Station* to = fr->selectWhere();

    // new event
    Event new_ev(evname, fr, to,
                clocktime, clocktime, clocktime+permanence, permanence);

    // schedule event
    schedule(new_ev);
    DR("Generated the event:");
    DD(new_ev.dump());
}

void System::schedule(Event& ev){
    FEL.schedule(ev);
}

void System::dump(){
    printf("////SYSTEM////:\n");
    printf("////FEL:\n");
    FEL.dump();
    printf("///STATIONS:\n");
    typedef vector<Station*>::iterator vsi;
    for(vsi it=stations.begin(); it!=stations.end(); ++it){
        (*it)->dump();
        try{
            // Only ServerStations have a queue, so we check the type with dynamic_cast
            ServerStation* stationWithQueue = dynamic_cast<ServerStation*>(*it);
            printf("/QUEUE AT THE STATION:");
            stationWithQueue->Q->dump();
        }catch(const std::bad_cast& ex){
            // station not of type ServerStation
        }
    }
    printf("////END SYSTEM////\n");
}
