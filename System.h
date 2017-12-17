
#ifndef SYSTEM_H
#define SYSTEM_H

#include "Station.h"
#include <vector>
#include <string>
#include "ListManager.h"
#include "GlobalTime.h"

using std::vector;
using std::string;

class System{
private:
    bool engine();
public:
    System(vector<Station*> a_stations, double MaxTime);

    vector<Station*> stations;
    Dll FEL;
    int reg;            // regeneration cycles
    bool start_engine;  // true until the simulation starts runs its first engine()
    double Max_Time;    // maximum time after which shut everything down
    int job_number;     // id for jobs/clients' names
    bool first_event;   // false until you create the first event ever

    Station* operator[](int i);
    bool hitRegeneration(); // check for regeneration point
    void simulate();
    void generate_event(Station* fr);
    void schedule(Event& ev);   // wrapper for Dll.schedule()
};

#endif // SYSTEM_H

