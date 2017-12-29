
#include "DEBUG.h"
#include "GlobalTime.h"
#include "WalkStat.h"
#include <set>
#include <map>
#include "Stat.h"
#include <cmath>
#include "StatNotifier.h"

WalkStat::WalkStat() :
    froms(), tos(), inside(), totalWalkTimes(0), firstTime(0){
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
    firstTime = clocktime;
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

        DER("@@ job in at %lf\n",inside[&ev]);

        return;
    }
    // a job is going out from the area of interest
    if(tos.find(ev.to) != tos.end()){
        // walk time (time elapsed from enter to exit)
        double walk_time = clocktime - inside[&ev];
        // pops out the event
        inside.erase(&ev);
        // adds the new walk time to the total
        totalWalkTimes += walk_time;

        DER("@@ job out at %lf. TotalWalkTime = %lf\n",clocktime, totalWalkTimes);

        return;
    }
    // nothing interesting
    return;
}

void WalkStat::update(){
    A->updateStat(totalWalkTimes, 1);
    nu->updateStat(clocktime - firstTime, 1);
    SAV->updateStat(totalWalkTimes*(clocktime-firstTime),1);
    reset();

    DER("@@ regeneration hit. Updating WalkStat.\n");
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
    DER("interval %lf rhat %lf\n", Interval, r_hat);
    return Interval;
}

bool WalkStat::reachedConfidence(double quantile, double level){
    double Interval = confidenceInterval(quantile);
    double nu_hat = nu->digest(StatBall::AVG);
    double r_hat = (nu_hat!=0) ? (A->digest(StatBall::AVG) / nu_hat) : (0);
    DER("confidence? %lf <? %lf\n",Interval,level*r_hat);
    return ( Interval < level*r_hat);
}
