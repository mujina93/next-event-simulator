
#ifndef SYSTEM_H
#define SYSTEM_H

#include "Station.h"
#include <vector>
#include <string>
#include "ListManager.h"
#include "GlobalTime.h"
#include "Subject.h"
#include "StatNotifier.h"
#include <set>
#include <map>
#include <utility>

using std::vector;
using std::string;
using std::set;
using std::map;
using std::pair;

class System : public Subject, public StatNotifier{
private:
    bool engine();                      // simulate one step
    vector<int> initial_state;          // initial values of N for all stations
    vector<Station*> MarkovStations;    // vector of stations with Negative Exponential random engine
    set<WalkStat*> confidenceGivers;    // WalkStat objects that can compute confidence intervals
    int _agglomeration;                 // how many regeneration do you want to agglomerate together
    int _agglomeration_count;           // counter for agglomerating cycles
public:
    System(vector<Station*> a_stations);

    vector<Station*> stations;
    Dll FEL;
    int reg;            // regeneration cycles
    //bool start_engine;  // true until the simulation starts runs its first engine()
    double Max_Time;    // maximum time after which shut everything down
    int job_number;     // id for jobs/clients' names
    bool first_event;   // false until you create the first event ever
    int Min_Cycles;  // max number of regeneration cycles
    double _quantile; // ...below...
    double _level;   // variables used to compute confidence interval and to stop simulation
    bool regeneration_testing; // true if you want to make a test run of the system and you want to study the frequency of states
    map< pair<vector<int>,Station*> , unsigned int > states; // map of system states at regeneration points, arrival Markov stations, and relative count of these occurrences
    pair< vector<int>, Station* > regeneration_state; // most frequent 'system state + arrival station' occurring at regeneration points

    Station* operator[](int i);
    bool hitRegeneration(Event& ev); // check for regeneration point
    void simulate(double MaxTime=100000, int MinCycles=10, double quantile=1.96, double level=0.1, int agglomeration_number=1);
    void generate_event(Station* fr);
    void schedule(Event& ev);   // wrapper for Dll.schedule()
    void dump();
    vector<int> get_state();    // gets the state (N in all stations)
    void addConfidenceGiver(WalkStat* ws);  // sets the confidence giver
    bool reachedConfidence();   // did you reach confidence? if so, you can stop the simulation
    void setRegenerationTesting(bool val); // sets to true or false the regeneration testing run
    void setRegenerationState(pair<vector<int>,Station*> vec); // sets manually the regeneration state
    pair<vector<int>,Station*> getRegenerationState();
};

#endif // SYSTEM_H

