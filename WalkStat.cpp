
#include "DEBUG.h"
#include "GlobalTime.h"
#include "WalkStat.h"
#include <set>
#include <map>
#include "Stat.h"
#include <cmath>
#include "StatNotifier.h"
#include <string>
#include <iostream>

using std::pair;
using std::cout;
using std::cerr;
using std::endl;

WalkStat::WalkStat(string name) :
    froms(), tos(), inside(),
    temporary_active_time(),
    totalWalkTimes(0), walkCompletionCount(0),
    _name(name){
    A = new StatBall();
    nu = new StatBall();
    SAV = new StatBall();
}

WalkStat::~WalkStat(){
    delete A;
    delete nu;
    delete SAV;
}

void WalkStat::reset(){
    totalWalkTimes = 0;
    walkCompletionCount = 0;
}

void WalkStat::addStartingPoint(Station *S){
    starting_station = S;
}

void WalkStat::watchFrom(Station* S){
    froms.insert(S);
}

void WalkStat::watchTo(Station* S){
    tos.insert(S);
}

void WalkStat::watchSystem(StatNotifier* sys){
    sys->addStatObserver(this);
}

void WalkStat::noticeEvent(Event& ev){ // called upon by notifyEvent()
    // a job is entering in the area of interest
    if(froms.find(ev.from) != froms.end()){
        // register the entering time
        //DES("@%s) Inserting %p into system\n",_name.c_str(),&ev);
        inside[ev.name] = clocktime;

        DES("@%s) job %s (from %d) in %d at %lf\n",_name.c_str(), ev.name.c_str(), ev.from->index, ev.to->index, inside[ev.name]);

        return;
    }
    // a job is going out from the area of interest
    if(tos.count(ev.to) > 0 && inside.count(ev.name) > 0){
        // walk time (time elapsed from enter to exit)
        // stores time that the job has passed inside the active system up to now
        // without returning to the delay station (staz. 0) in the meanwhile
        if(temporary_active_time.count(ev.name) <= 0){
            // if the key,value does not exist, create it
            temporary_active_time[ev.name] = clocktime - inside[ev.name];
        }else{
            // else, add the value
            temporary_active_time[ev.name] += clocktime - inside[ev.name];
        }

        // if the job has completed a cycle of the system (it has visited the delay station again)
        // save its temporary_active_time by adding it to the totalWalkTimes (which will make up for
        // an instance of the active time)
        ///cerr << ev.to->index << " " << starting_station->index << std::endl;
        if(ev.to->index == starting_station->index){
            // adds the new walk time to the total
            totalWalkTimes += temporary_active_time[ev.name];
            // increase counter of walk completions
            walkCompletionCount++;
            // resets partial time for the event
            temporary_active_time[ev.name] = 0;
        }

        //DES("@%s) Removing %p from system\n",_name.c_str(),&ev);
        DES("@%s) job %s out. From %d to %d at %lf. (Entered at: %lf). TotalWalkTime = %lf, completions = %1.0lf\n",_name.c_str(), ev.name.c_str(), ev.from->index, ev.to->index, clocktime, inside[ev.name], totalWalkTimes, walkCompletionCount);

        // pops out the event
        inside.erase(ev.name);

        return;
    }
    // nothing interesting
    return;
}

void WalkStat::update(){ // called upon by notifyRegeneration()
    A->updateStat(totalWalkTimes, 1);
    nu->updateStat(walkCompletionCount, 1);
    SAV->updateStat(totalWalkTimes * walkCompletionCount,1);
    reset();

    DES("@%s) regeneration hit, at time: %lf. Updating. total walk times (A) = %lf, completions (nu) = %1.0lf, time*completions (SAV) = %lf\n",_name.c_str(),clocktime,A->sum,nu->sum,SAV->sum);
}

int WalkStat::getWalkCompletionCount(){
    return walkCompletionCount;
}

double WalkStat::confidenceInterval(double probability){
    // r_hat
    double nu_hat = nu->digest(StatBall::AVG);
    double r_hat = (nu_hat!=0) ? (A->digest(StatBall::AVG) / nu_hat) : (0);
    // S's
    double S_AA = A->sumSq;
    double S_vv = nu->sumSq;
    double S_Av = SAV->sum;
    //double S_v = nu->sum;
    // p
    double p = A->Size;
    // (s^_Z)^2
    double s2_Z = ((p-1)!=0)?((S_AA - 2*r_hat*S_Av + r_hat*r_hat*S_vv)/(p-1)):(0);
    // Delta
    double Delta = sqrt(s2_Z/p) / nu_hat;
    // interval width
    double quantile = estimator.quantile2tailed(probability);
    double Interval = 2 * quantile * Delta;
    DES("@%s) nu_hat %lf avgA %lf interval %lf rhat %lf\n", _name.c_str(), nu_hat, A->digest(StatBall::AVG), Interval, r_hat);

    // save everything in the interval estimator object
    estimator.setEstimate(r_hat);
    estimator.setInterval(Interval, probability);

    // useless return
    return estimator.interval.value;
}

bool WalkStat::reachedConfidence(double probability, double precision){
    // computes confidence interval for given probability
    // the results are set in the object 'estimator'
    confidenceInterval(probability);
    _precision_on_estimate = precision;
    DES("@%s) confidence? %lf <? %lf\n",_name.c_str(), estimator.interval.value,precision*estimator.estimate);
    return estimator.satisfiesPrecision(precision);
}

void WalkStat::dump(){
    double Interval = estimator.interval.value;
    double r_hat = estimator.estimate;
    double probability = estimator.interval.probability;
    //fprintf(stdout,"confidence? %lf <? %lf\n",Interval,level*r_hat);
    cout << "Statistics for: " << _name << "\n";
    fprintf(stdout, "r_hat: %lf, interval: %lf, covering probability: %lf, precision: %lf\n",
            r_hat, Interval, probability, _precision_on_estimate);
}

pair<double,double> WalkStat::ExtremesOfInterval(){
    pair<double,double> min_max_confidence_interval(estimator.estimate - estimator.interval.value / 2, estimator.estimate + estimator.interval.value / 2);
    return min_max_confidence_interval;
}
