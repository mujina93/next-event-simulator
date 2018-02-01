
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

using std::cout;

WalkStat::WalkStat(string name) :
    froms(), tos(), inside(),
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
    if(tos.find(ev.to) != tos.end() && inside.find(ev.name) != inside.end()){
        // walk time (time elapsed from enter to exit)
        double walk_time = clocktime - inside[ev.name];
        // adds the new walk time to the total
        totalWalkTimes += walk_time;
        // increase counter of walk completions
        walkCompletionCount++;

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
    DER("@%s) nu_hat %lf avgA %lf interval %lf rhat %lf\n", _name.c_str(), nu_hat, A->digest(StatBall::AVG), Interval, r_hat);

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
    DER("@%s) confidence? %lf <? %lf\n",_name.c_str(), estimator.interval.value,precision*estimator.estimate);
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
