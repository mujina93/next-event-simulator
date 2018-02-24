
#ifndef WALKSTAT_H
#define WALKSTAT_H

#include "Stat.h"
#include "Observer.h"
#include "Events.h"
#include <set>
#include <map>
#include <string>
#include "Estimator.h"
#include <utility>

using std::set;
using std::map;
using std::string;
using std::pair;

class Station;
class StatNotifier;

class WalkStat{
public:
    WalkStat(string name);
    ~WalkStat();

    Station* starting_station; // considered as turning point for cycles in the system
    set<Station*> froms;    // entering points for the area of interest
    set<Station*> tos;      // exit points for the area of interest
    map<string,double> inside;  // (job's name,entering time) pairs, to register a job which is walking into the area of interest and the entering time
    map<string,double> temporary_active_time; // stores partial values of time passed in active part of system by a job
    double totalWalkTimes;  // total of the walk times (every time a job completes a walk in the area of interest, add its time to this)
    double walkCompletionCount;  // counts the job that have completed a walk during the regeneration period
    StatBall* A;            // A_j = total walk time during a regeneration cycle
    StatBall* nu;           // nu_j = regeneration cycle's length
    StatBall* SAV;          // SAV_j = A_j*nu_j
    string _name;            // this object's name
    StdNormEstimator estimator; // purpose of WalkStat is to provide this object (estimate + confidence interval)
    double _precision_on_estimate; // how small should the confidence interval be on the final estimate

    // the duty of a WalkStat (= Observer) is to watchSystem() a system
    // then, the system will notify() the WalkStat, which will notice() and update()
    void addStartingPoint(Station* S);
    void watchSystem(StatNotifier* sys);
    void watchFrom(Station* S); // add S to 'froms'. When a job leaves from this station, watch it
    void watchTo(Station* S); // add S to 'tos'. When a job arrives at this station, register the time it has walked until now
    void reset();       // call when starting a regeneration cycle
    void noticeEvent(Event& ev); // register an event and its walk time if it is going in or out from the area of interest
    void update(); // updateStat(y, x) from StatBall -- use this to add totalWalkTime as y value and elapsed time (current clocktime - firstTime) as x value
    double confidenceInterval(double probability); // confidence interval
    bool reachedConfidence(double probability, double precision); // is Interval < precision*r_hat ?
    void dump();
    double validate(double theoretical_value);
    pair<double,double> ExtremesOfInterval();
};

#endif // WALKSTAT_H

