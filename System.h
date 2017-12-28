
#ifndef SYSTEM_H
#define SYSTEM_H

#include "Station.h"
#include <vector>
#include <string>
#include "ListManager.h"
#include "GlobalTime.h"
#include "Subject.h"
#include "StatNotifier.h"

using std::vector;
using std::string;

class System : public Subject, public StatNotifier{
private:
    bool engine();                      // simulate one step
    vector<int> initial_state;          // initial values of N for all stations
    vector<Station*> MarkovStations;    // vector of stations with Negative Exponential random engine
public:
    System(vector<Station*> a_stations, double MaxTime, int MaxCycles);

    vector<Station*> stations;
    Dll FEL;
    int reg;            // regeneration cycles
    //bool start_engine;  // true until the simulation starts runs its first engine()
    double Max_Time;    // maximum time after which shut everything down
    int job_number;     // id for jobs/clients' names
    bool first_event;   // false until you create the first event ever
    int Max_Cycles;  // max number of regeneration cycles

    Station* operator[](int i);
    bool hitRegeneration(Event& ev); // check for regeneration point
    void simulate();
    void generate_event(Station* fr);
    void schedule(Event& ev);   // wrapper for Dll.schedule()
    void dump();
    vector<int> get_state();    // gets the state (N in all stations)
};

#endif // SYSTEM_H

