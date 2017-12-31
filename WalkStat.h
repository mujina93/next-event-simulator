
#ifndef WALKSTAT_H
#define WALKSTAT_H

#include "Stat.h"
#include "Observer.h"
#include "Events.h"
#include <set>
#include <map>
#include <string>

using std::set;
using std::map;
using std::string;

class Station;
class StatNotifier;

class WalkStat{
public:
    WalkStat(string name);
    ~WalkStat();

    set<Station*> froms;    // entering points for the area of interest
    set<Station*> tos;      // exit points for the area of interest
    map<Event*,double> inside;  // (event,entering time) pairs, to register a job which is walking into the area of interest and the entering time
    double totalWalkTimes;  // total of the walk times (every time a job completes a walk in the area of interest, add its time to this)
    double walkCompletionCount;  // counts the job that have completed a walk during the regeneration period
    StatBall* A;            // A_j = total walk time during a regeneration cycle
    StatBall* nu;           // nu_j = regeneration cycle's length
    StatBall* SAV;          // SAV_j = A_j*nu_j
    string _name;            // this object's name

    // the duty of a WalkStat (= Observer) is to watchSystem() a system
    // then, the system will notify() the WalkStat, which will notice() and update()
    void watchSystem(StatNotifier* sys);
    void watchFrom(Station* S); // add S to 'froms'. When a job starts from this station, watch it
    void watchTo(Station* S); // add S to 'tos'. When a job arrives at this station, register the time it has walked until now
    void reset();       // call when starting a regeneration cycle
    void noticeEvent(Event& ev); // register an event and its walk time if it is going in or out from the area of interest
    void update(); // updateStat(y, x) from StatBall -- use this to add totalWalkTime as y value and elapsed time (current clocktime - firstTime) as x value
    double confidenceInterval(double quantile); // confidence interval
    bool reachedConfidence(double quantile, double level); // is Interval < level*r_hat ?
    void dump(double quantile, double level);
};

#endif // WALKSTAT_H

