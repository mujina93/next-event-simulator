
#ifndef WALKSTATBALL_H
#define WALKSTATBALL_H

#include "Stat.h"
#include "Observer.h"
#include "Events.h"
#include <set>
#include <map>

using std::set;
using std::map;

class Station;

class WalkStatBall : public StatBall {
public:
    WalkStatBall();

    set<Station*> froms;    // entering points for the area of interest
    set<Station*> tos;      // exit points for the area of interest
    map<Event*,double> inside;  // (event,entering time) pairs, to register a job which is walking into the area of interest and the entering time
    double totalWalkTimes;  // total of the walk times (every time a job completes a walk in the area of interest, add its time to this)
    double firstTime;       // starting time. When a regeneration cycle is completed, register the total time elapsed from this moment. Then reset this

    void watchFrom(Station* S); // add S to 'froms'. When a job starts from this station, watch it
    void watchTo(Station* S); // add S to 'tos'. When a job arrives at this station, register the time it has walked until now
    void reset();       // call when starting a regeneration cycle
    void noticeEvent(Event& ev); // register an event and its walk time if it is going in or out from the area of interest
    void update(); // updateStat(y, x) from StatBall -- use this to add totalWalkTime as y value and elapsed time (current clocktime - firstTime) as x value
};

#endif // WALKSTATBALL_H

