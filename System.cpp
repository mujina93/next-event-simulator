
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
#include <set>
#include <map>
#include <utility>
#include "Matrix.h"

using std::vector;
using std::string;
using std::to_string;
using std::set;
using std::map;
using std::cout;
using std::endl;
using std::pair;
using std::sort;

System::System(vector<Station*> a_stations) :
    initial_state(), MarkovStations(), _agglomeration(0), _agglomeration_count(0), _hit_first_reg(false),
    stations(a_stations), FEL(), reg(0),
    Max_Time(0), job_number(0), first_event(false),
    Min_Cycles(0), _confidenceIntervalProbability(0),
    _confidenceIntervalPrecision(0),
    regeneration_testing(false){
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
    //double oldtime = clocktime;
    clocktime = pop_ev.leaving_at;
    // notify WalkStat
    // (WalkStat objects will call noticeEvent() to consider if the job is
    // entering or going out from the zone of interest. If it is
    // going out, the elapsed time (time spent by job inside the
    // zone of interest) is registered and added to the StatBalls)
    if(regeneration_testing==false && _hit_first_reg==true){
        notifyEvent(pop_ev);
    }
    // did you hit a regeneration point?
    bool hit_reg = hitRegeneration(pop_ev);
    // if this is the first time, start the real simulation
    // (only valid for true runs, not for test runs)
    if(regeneration_testing==false){
        if(hit_reg == true && _hit_first_reg==false){
            _hit_first_reg = true;
        }
        // check for end of simulation (only for true runs)
        if(_hit_first_reg==true){ // if this is a true run (and if the first regeneration point was reached)
            // check for end of simulation (must have: regeneration point, reached confidence, and enough cycles)
            if(hit_reg && reachedConfidence() && reg > Min_Cycles){
                DER("reached confidence.\nEND OF SIMULATION\n");
                return true;  // do halt!
            }
        }
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
    } // else, processDeparture returned no useful event. Nothing to do

    // the job arrives to StazTo. StazTo processes now the event
    // it can serve and recast it, or it can enqueue it.
    Station* StazTo = pop_ev.to;
    DD(fprintf(stderr,"ARR) Station %d: ",StazTo->index));
    Event new_ev = StazTo->processArrival(pop_ev);
    if( !new_ev.isNull() ){
        // A new event was cast. Insert into FEL
        schedule(pop_ev);
    } //else, pop_ev was enqueued. Nothing to do.

    // notify the Observers (if any)
    // (in our case, notify the MPD station that could want
    // to dequeue and recast and schedule immediately a job)
    notify();

    // if simulation is too long, abort
    if(clocktime > Max_Time){
        if(regeneration_testing==false){
            fprintf(stderr, "Simulation took too much!\nAborted\n");
        } else {
            fprintf(stderr, "End of test run. Information about regeneration points was collected.\n");
        }
        return true; // halt! stop the simulation
    } else {
        return false; // don't halt!
    }
}

bool System::hitRegeneration(Event& ev){
    bool hitReg = false;
    // in case of test run, consider all regeneration points
    if(regeneration_testing==true){
        // a regeneration point is an arrival to a Markov station (one with NegExp service times)
        if(std::find(MarkovStations.begin(),MarkovStations.end(),ev.to)!=MarkovStations.end()){
        // MarkovStations contains the station where ev is heading
        hitReg = true;
        }
    } else {
    // in a true run, only a particular state is considered as the regeneration state.
    // this function returns true if THAT PARTICULAR STATE IS HIT, AND, ONLY EVERY
    // '_agglomeration' CYCLES.
        if(ev.to->index==regeneration_state.second->index && get_state() == regeneration_state.first){
            _agglomeration_count++;
            if(_agglomeration_count==_agglomeration-1){
                DES("Hit regeneration! At time %lf\n",clocktime);
                // you hit _agglomeration regeneration cycles!
                // count one big cycle!
                hitReg = true;
                // reset counter
                _agglomeration_count = 0;
            }
        }
    }
    // if you hit regeneration...
    if(hitReg == true){
        reg++;  // increase counter that counts how many cycles you had

        // if this is a preliminar test run, save the system states at regeneration points
        if(regeneration_testing==true){
            // saves the system state and the station when ev is arriving
            pair<vector<int>, Station*> element(get_state(), ev.to);
            states[element] += 1;
        }
        // if this is a true run, notify WalkStatBalls for computing statistics
        else {
            notifyRegeneration();
        }
    }
    // else
    return hitReg;
}

void System::simulate(double MaxTime, int MinCycles, double confidenceIntervalProbability, double precision, int agglomeration_number){
    // simulation parameters
    Min_Cycles = MinCycles;
    Max_Time = MaxTime;
    _confidenceIntervalProbability = confidenceIntervalProbability;
    _confidenceIntervalPrecision = precision;
    _agglomeration = agglomeration_number;

    // SIMULATE
    bool halt = false;
    while(!halt){
        halt = engine();
    }

    // PRINT RESULTS
    // if this is a simulation run, print the count for all states that occurred during regeneration points
    if(regeneration_testing==true){
        cout << "SIMULATION TEST RUN. CHECKING OCCURRED STATES AT REGENERATION POINTS\n";
        #if DEBUG==1
        cout << "Stations:\n";
        for(vector<Station*>::iterator vsi = stations.begin(); vsi!=stations.end(); ++vsi){
            cout << (*vsi)->index << " ";
        }
        cout << "\n";
        cout << "State | arrival station : count\n";
        #endif
        // transform map into vector of pairs, so that you can easily sort the elements by value (map->second)
        vector< pair< pair<vector<int>,Station*> , unsigned int > > pairs;
        for(auto itr = states.begin(); itr!=states.end(); ++itr){
            pairs.push_back(*itr);
        }
        // sort the map (decreasing)
        sort(pairs.begin(), pairs.end(),
            [=](pair<pair<vector<int>,Station*>,unsigned int>& a, pair<pair<vector<int>,Station*>,unsigned int>& b){
                return a.second > b.second;
            }
        );
        #if DEBUG==1
        // print out state, arrival stations, count
        vector< pair < pair<vector<int>,Station*> , unsigned int > >::iterator vpi; // iterator over pairs
        vector<int>::iterator vit;
        for(vpi = pairs.begin(); vpi!=pairs.end(); ++vpi){
            // print state (vector)
            for(vit = (*vpi).first.first.begin(); vit!=(*vpi).first.first.end(); ++vit){
                cout << (*vit) << " ";
            }
            cout << "| ";
            // print arrival station (index)
            cout << (*vpi).first.second->index << " : ";
            // print count (how many times that vector occurred)
            cout << (*vpi).second << endl;
        }
        #endif
        // saving most frequent regeneration state
        regeneration_state = pairs[0].first;
        cout << "Saving the most frequent state: " << endl;
        for(vector<int>::iterator vii = regeneration_state.first.begin(); vii!=regeneration_state.first.end(); ++vii){
            cout << *vii << " ";
        }
        cout << "| " << regeneration_state.second->index << endl;
    } else {
        // true simulation ended. Print results
        for(map<string,WalkStat*>::iterator swi = confidenceGivers.begin(); swi!=confidenceGivers.end(); ++swi){
            swi->second->dump();
        }
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

bool System::reachedConfidence(){
    bool answer = true;
    typedef map<string,WalkStat*>::iterator swi;
    for(swi it=confidenceGivers.begin(); it!=confidenceGivers.end(); ++it){
        answer = answer && it->second->reachedConfidence(_confidenceIntervalProbability,_confidenceIntervalPrecision);
    }
    return answer;
}

void System::schedule(Event& ev){
    FEL.schedule(ev);
}

void System::addConfidenceGiver(WalkStat* ws){
    // save the walkstat using its short name as key
    confidenceGivers[ws->_name] = ws;
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

void System::setRegenerationTesting(bool val){
    regeneration_testing = val;
}

void System::setRegenerationState(pair<vector<int>,Station*> state){
    regeneration_state = state;
}

pair<vector<int>,Station*> System::getRegenerationState(){
    return regeneration_state;
}

int System::getNumberOfStations(){
    return stations.size();
}

pair<double,double> System::getIntervalExtremesResults(string walkStatName){
    return confidenceGivers[walkStatName]->ExtremesOfInterval();
}

















