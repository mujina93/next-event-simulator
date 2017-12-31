
#include "DEBUG.h"
#include "GlobalTime.h"
#include "WalkStat.h"
#include <set>
#include <map>
#include "Stat.h"
#include <cmath>
#include "StatNotifier.h"
#include <string>

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

void WalkStat::noticeEvent(Event& ev){
    // a job is entering in the area of interest
    if(froms.find(ev.from) != froms.end()){
        // register the entering time
        inside[&ev] = clocktime;

        DER("@%s) job %s in %d at %lf\n",_name.c_str(), ev.name.c_str(), ev.from->index, inside[&ev]);

        return;
    }
    // a job is going out from the area of interest
    if(tos.find(ev.to) != tos.end() && inside.find(&ev) != inside.end()){
        // walk time (time elapsed from enter to exit)
        double walk_time = clocktime - inside[&ev];
        // pops out the event
        inside.erase(&ev);
        // adds the new walk time to the total
        totalWalkTimes += walk_time;
        // increase counter of walk completions
        walkCompletionCount++;

        DER("@%s) job %s out of %d at %lf. TotalWalkTime = %lf, completions = %1.0lf\n",_name.c_str(), ev.name.c_str(), ev.to->index, clocktime, totalWalkTimes, walkCompletionCount);

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

    DER("@%s) regeneration hit. Updating WalkStat.\n",_name.c_str());
}

double WalkStat::confidenceInterval(double quantile){
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
    double Interval = 2 * quantile * Delta;
    DER("@%s) nu_hat %lf avgA %lf interval %lf rhat %lf\n", _name.c_str(), nu_hat, A->digest(StatBall::AVG), Interval, r_hat);
    return Interval;
}

bool WalkStat::reachedConfidence(double quantile, double level){
    double Interval = confidenceInterval(quantile);
    double nu_hat = nu->digest(StatBall::AVG);
    double r_hat = (nu_hat!=0) ? (A->digest(StatBall::AVG) / nu_hat) : (0);
    DER("@%s) confidence? %lf <? %lf\n",_name.c_str(), Interval,level*r_hat);
    return ( Interval < level*r_hat);
}

void WalkStat::dump(double quantile, double level){
    double Interval = confidenceInterval(quantile);
    double nu_hat = nu->digest(StatBall::AVG);
    double r_hat = (nu_hat!=0) ? (A->digest(StatBall::AVG) / nu_hat) : (0);
    fprintf(stdout,"confidence? %lf <? %lf\n",Interval,level*r_hat);
}
