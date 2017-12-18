
#include "Events.h"
#include "ListManager.h"
#include "Stat.h"
#include "rngs.h"
#include "rvgs.h"
#include "Station.h"
#include "System.h"
#include <map>
#include <vector>

#include "GlobalTime.h" // extern declaration of global time
double clocktime = 0;        // actual definitio of global time

using std::map;
using std::vector;

System* initialize();
System* dummy();

int main(){
    System* sys = initialize();
    sys->simulate();
    delete sys;
    return 0;
}

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
    System* mysys = new System(stations, 100000);
    return mysys;
}

System* initialize(){
    // create and initialize stations
    vector<Station*> stations;
    double* params = new double[1];
    // staz 0 - initialized with 20 clients inside
    params[0] = 5000.0;
    Station* delay = new DelayStation(4, 0, RNG::EXP, params);
    stations.push_back(delay);
    // staz 1 - reserve, MPD=10
    Station* reserve = new MPD(0, 1, 1);
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

    // add stations for MPD to watch (MPD pointer needed for polimorphism)
    MPD* MPDreserve = static_cast<MPD*>(reserve);
    MPDreserve->watch(swapin);
    MPDreserve->watch(CPU);
    MPDreserve->watch(IO1);
    MPDreserve->watch(IO2);

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
    System* mysys = new System(stations, 100000);

    delete params;
    return mysys;
}
