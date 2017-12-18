
#include "DEBUG.h"

#include "System.h"
#include <cstdio>
#include <string>
#include "GlobalTime.h"
#include "Events.h"
#include <iostream>

using std::vector;
using std::string;
using std::to_string;

System::System(vector<Station*> a_stations, double MaxTime) :
    stations(a_stations), FEL(), reg(0), start_engine(true),
    Max_Time(MaxTime), job_number(0), first_event(false) {
    DR("Creating the system ---");
    // bootstrap: generate the first events for all stations which have clients
    typedef vector<Station*>::iterator vsi;
    for(vsi it=stations.begin(); it!=stations.end(); ++it){
        DR("--- At station: ");
        DD((*it)->dump());
        for(int i=0; i<((*it)->N); i++){
            generate_event(*it);
        }
    }
    DR("--- System created");
}

Station* System::operator[](int i){
    return stations[i];
}

bool System::engine(){
    DR("engine:");
    // pop event
    Event pop_ev = FEL.pop();

    // update clock
    double oldtime = clocktime;
    clocktime = pop_ev.leaving_at;

    if(start_engine || !hitRegeneration()){
        DR("Processing the event");
        DD(pop_ev.dump());

        // the job is leaving StazFrom => so it frees up space for a
        // dequeue (if there are pending jobs in StazFrom)
        Station* StazFrom = pop_ev.from;
        DD(fprintf(stderr,"***Station %d here: ",StazFrom->index));
        Event dequeued = StazFrom->processDeparture(pop_ev);
        if( !dequeued.isNull() ){
            FEL.schedule(dequeued);
        } else {
            // processDeparture returned no useful event. Nothing to do
        }

        // the job arrives to StazTo. StazTo processes now the event
        // it can serve and recast it, or it can enqueue it.
        Station* StazTo = pop_ev.to;
        DD(fprintf(stderr,"***Station %d here: ",StazTo->index));
        Event new_ev = StazTo->processArrival(pop_ev);
        if( !new_ev.isNull() ){
            // A new event was cast. Insert into FEL
            FEL.schedule(pop_ev);
        } else {
            // pop_ev was enqueued. Nothing to do.
        }

        // the simulation has started. Set the flag.
        if(start_engine==true)
            start_engine = false;
        bool halt = false;
        return halt;
    } else {
        bool halt = true;
        return halt;
    }

    // if simulation is too long, abort
    if(clocktime > Max_Time){
        bool halt = true;
        fprintf(stderr, "Simulation took too much!\nAborted\n");
        return halt;
    }
}

bool System::hitRegeneration(){
    int NumberAtDelay = stations[0]->N;
    if(NumberAtDelay==4){
        DR("Hit regeneration");
        return true;
    } else{
        return false;
    }
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
