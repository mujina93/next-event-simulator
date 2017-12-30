
#include "Events.h"
#include "ListManager.h"
#include "Stat.h"
#include "rngs.h"
#include "rvgs.h"
#include "Station.h"
#include "System.h"
#include <map>
#include <vector>
#include "WalkStat.h"

#include "GlobalTime.h" // extern declaration of global time
double clocktime = 0;   // actual definitio of global time

using std::map;
using std::vector;

System* initialize();
System* approximate();
System* dummy();

int main(){
    System* sys = initialize();
    //            max_time min_cycles quantile level
    sys->simulate(1000000,     20,      1.96,   0.1);
    delete sys;
    return 0;
}
// simple system
System* dummy(){
    // create and initialize stations
    vector<Station*> stations;
    // staz 0 -
    double* params = new double[1]; params[0] = 30;
    Station* zero = new DelayStation(4, 0,RNG::EXP, params);
    stations.push_back(zero);
    // staz 1 -
    params[0] = 40;
    Station* one = new ServerStation(0, 1, RNG::EXP, params);
    stations.push_back(one);
    // staz 2 -
    params = new double[3];
    params[0] = 0.8; params[1] = 15; params[2] = 75;
    Station* two = new SliceStation(0, 2, RNG::HYPEXP, params, 3);
    stations.push_back(two);

    // glue stations together - set routes
    map<Station*,double> routes;
    // from zero
    routes[one] = 1;
    zero->setRoutes(routes);
    // from one
    routes.clear(); routes[two] = 1;
    one->setRoutes(routes);
    // from two
    routes.clear(); routes[zero] = 1;
    two->setRoutes(routes);

    // build and return the system object
    // the Future Event List is created inside the System
    System* mysys = new System(stations);
    return mysys;
}
// true system
System* initialize(){
    // create and initialize stations
    vector<Station*> stations;
    double* params = new double[1];
    // staz 0 - initialized with 20 clients inside
    params[0] = 5000.0;
    Station* delay = new DelayStation(20, 0, RNG::EXP, params);
    stations.push_back(delay);
    // staz 1 - reserve, MPD=10
    Station* reserve = new MPD(0, 1, 10);
    stations.push_back(reserve);
    // staz 2 - swapin
    params[0] = 210;  // mu
    Station* swapin = new ServerStation(0, 2, RNG::EXP, params);
    stations.push_back(swapin);
    // staz 3 - CPU hyperexponential, quantum=3
    params = new double[3];
    params[0] = 0.8;    // alpha
    params[1] = 15;     // mu1
    params[2] = 75;     // mu2
    Station* CPU = new SliceStation(0, 3, RNG::HYPEXP, params, 3);
    stations.push_back(CPU);
    // staz 4 - IO
    params = new double[1]; params[0] = 40;
    Station* IO1 = new ServerStation(0, 4, RNG::EXP, params);
    stations.push_back(IO1);
    // staz 5 - IO
    params = new double[1]; params[0] = 180;
    Station* IO2 = new ServerStation(0, 5, RNG::EXP, params);
    stations.push_back(IO2);

    // glue stations together - set routes
    map<Station*,double> routes;
    // from delay (0)
    routes[reserve] = 1;
    delay->setRoutes(routes);
    // from reserve (1)
    routes.clear(); routes[swapin] = 1;
    reserve->setRoutes(routes);
    // from swapin (2)
    routes.clear(); routes[CPU] = 1;
    swapin->setRoutes(routes);
    // from CPU (3)
    routes.clear();
    routes[IO1] = 0.65; routes[IO2] = 0.25;
    routes[delay] = 0.1*0.4; routes[reserve] = 0.1*0.6;
    CPU->setRoutes(routes);
    // from IO1 (4)
    routes.clear(); routes[CPU] = 1;
    IO1->setRoutes(routes);
    // from IO2 (5)
    routes.clear(); routes[CPU] = 1;
    IO2->setRoutes(routes);

    // build and return the system object
    // the Future Event List is created inside the System
    System* mysys = new System(stations);

    // add system for MPD to watch
    MPD* MPDreserve = static_cast<MPD*>(reserve); //(MPD pointer needed for polymorphism)
    MPDreserve->watch(mysys);
    // add stations to be checked by MPD
    MPDreserve->addUnderControl(CPU);
    MPDreserve->addUnderControl(IO1);
    MPDreserve->addUnderControl(IO2);

    // WalkStatBalls that watch the system and compute walk times
    // (in our case: Response time...
    WalkStat* ResponseTimeStatBall = new WalkStat();
    ResponseTimeStatBall->watchSystem(mysys);
    ResponseTimeStatBall->watchFrom(delay);
    ResponseTimeStatBall->watchTo(delay);
    // ...and Active time)
    WalkStat* ActiveTimeStatBall = new WalkStat();
    ActiveTimeStatBall->watchSystem(mysys);
    ActiveTimeStatBall->watchFrom(reserve);
    ActiveTimeStatBall->watchTo(delay);
    ActiveTimeStatBall->watchTo(reserve);

    // add them as confidence givers for the system
    mysys->addConfidenceGiver(ResponseTimeStatBall);
    mysys->addConfidenceGiver(ActiveTimeStatBall);

    delete params;
    return mysys;
}
// approximated system
System* approximate(){
    // create and initialize stations
    vector<Station*> stations;
    double* params = new double[1];
    // staz 0 - initialized with 20 clients inside
    params[0] = 5000.0;
    Station* delay = new DelayStation(20, 0, RNG::EXP, params);
    stations.push_back(delay);
    // staz 2 - swapin
    params[0] = 210;  // mu
    Station* swapin = new ServerStation(0, 2, RNG::EXP, params);
    stations.push_back(swapin);
    // staz 3 - CPU hyperexponential, quantum=3
    params = new double[3];
    params[0] = 3;
    Station* CPU = new ServerStation(0, 3, RNG::EXP, params);
    stations.push_back(CPU);
    // staz 4 - IO
    params = new double[1]; params[0] = 40;
    Station* IO1 = new ServerStation(0, 4, RNG::EXP, params);
    stations.push_back(IO1);
    // staz 5 - IO
    params = new double[1]; params[0] = 180;
    Station* IO2 = new ServerStation(0, 5, RNG::EXP, params);
    stations.push_back(IO2);

    // glue stations together - set routes
    map<Station*,double> routes;
    // from delay (0)
    routes[swapin] = 1;
    delay->setRoutes(routes);
    routes.clear();
    // from swapin (2)
    routes[CPU] = 1;
    swapin->setRoutes(routes);
    routes.clear();
    // from CPU (3)
    routes[IO1] = 0.065; routes[IO2] = 0.025;
    routes[delay] = 0.01*0.4; routes[swapin] = 0.01*0.6;
    routes[CPU] = 0.9;
    CPU->setRoutes(routes);
    routes.clear();
    // from IO1 (4)
    routes[CPU] = 1;
    IO1->setRoutes(routes);
    routes.clear();
    // from IO2 (5)
    routes[CPU] = 1;
    IO2->setRoutes(routes);
    routes.clear();

    // build and return the system object
    // the Future Event List is created inside the System
    System* mysys = new System(stations);

    // WalkStatBalls that watch the system and compute walk times
    // (in our case: Response time...
    WalkStat* ResponseTimeStatBall = new WalkStat();
    ResponseTimeStatBall->watchSystem(mysys);
    ResponseTimeStatBall->watchFrom(delay);
    ResponseTimeStatBall->watchTo(delay);
    // ...and Active time)
    WalkStat* ActiveTimeStatBall = new WalkStat();
    ActiveTimeStatBall->watchSystem(mysys);
    ActiveTimeStatBall->watchFrom(swapin);
    ActiveTimeStatBall->watchTo(delay);
    ActiveTimeStatBall->watchTo(swapin);

    // add them as confidence givers for the system
    mysys->addConfidenceGiver(ResponseTimeStatBall);
    mysys->addConfidenceGiver(ActiveTimeStatBall);

    delete params;
    return mysys;
}
