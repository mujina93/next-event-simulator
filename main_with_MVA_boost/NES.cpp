
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
#include "MVA.h"
#include <iostream>
#include <utility>

#include "GlobalTime.h" // extern declaration of global time
double clocktime = 0;   // actual definitio of global time

using std::map;
using std::vector;
using std::cerr;
using std::cout;
using std::pair;

System* createSystem();
System* approximateSystemNoMPD();
System* dummy();

typedef System* (*builder)(void); // type that denotes a function that builds a system
struct validation_interval_results {
    map<string, vector<pair<double,double>> > data;
};
validation_interval_results RunSimulations(int number_of_runs,
                                            builder SystemBuilderFunction,
                                            System* burn_in_system,
                                            double max_time,
                                            int min_reg_points,
                                            double prob,
                                            double precision,
                                            bool agglomerateBasedOnCompletions,
                                            int agglomeration);
pair<double,double> validate(double theoretical_value, vector<pair<double,double>> intervals);

int main(){

    /// MVA analysis
    System* approxSys = approximateSystemNoMPD();
    vector<int> active_stations = {2,3,4};
    //  precision   stations  max_clients
    MVA< double,       5  ,        30  > mvaAnalyzer(approxSys,active_stations);
    // MVA analysis
    mvaAnalyzer.bottleneckAnalysis();
    mvaAnalyzer.MVA_LI_D();
    mvaAnalyzer.print_results();
    mvaAnalyzer.plot_results();

    // store theoretical results
    pair<double,double> Response_Active_Times = mvaAnalyzer.getResponseTime_ActiveTime(20);
    // cleanup
    delete approxSys;

    /// test run
    System* test_sys = approximateSystemNoMPD();
    test_sys->setRegenerationTesting(true);
    //                 max_time
    test_sys->simulate(1000000);

    /// true runs
    validation_interval_results Results = RunSimulations(100, approximateSystemNoMPD, test_sys, 1000000000, 10, 0.9, 0.1, true, 40);
    // cleanup
    delete test_sys;

    /// Validation
    pair<double,double> Result_Response = validate(Response_Active_Times.first, Results.data["rsp"]);
    pair<double,double> Result_Active = validate(Response_Active_Times.second, Results.data["act"]);
    // show results
    cout << "\nValidation Results for Response time: " << Result_Response.first * 100 << "% intervals covering theoretical value, ";
    cout << Result_Response.second * 100 << "% asymmetry in non-covering intervals\n";
    cout << "\nValidation Results for Active time: " << Result_Active.first * 100 << "% intervals covering theoretical value, ";
    cout << Result_Active.second * 100 << "% asymmetry in non-covering intervals\n";

    return 0;
}

pair<double,double> validate(double theoretical_value, vector<pair<double,double>> intervals){
    cout << "\nValidating for theoretical value: " << theoretical_value << "\n";
    double percentage_in = 0;
    double asymmetry = 0;
    for(unsigned int i=0; i<intervals.size(); i++){
        // check if interval covers theoretical value or not
        cout << "Interval: [" << intervals[i].first << ", " << intervals[i].second << "] : ";
        if(theoretical_value >= intervals[i].first && theoretical_value <= intervals[i].second){
            percentage_in++;
            cout << "in!";
        } else if (theoretical_value <= intervals[i].first){
            cout << "too high";
        } else {
            cout << "too low";
        }
        cout << '\n';
        // are you over-valueing or under-valueing it?
        if ( (intervals[i].first + intervals[i].second)/2 > theoretical_value){
            asymmetry++;
        } else {
            asymmetry--;
        }
    }
    percentage_in /= intervals.size();
    asymmetry     /= intervals.size();
    pair<double,double> result(percentage_in, asymmetry);
    return result;
}

validation_interval_results RunSimulations(int number_of_runs,
                    builder SystemBuilderFunction,
                    System* burn_in_system,
                    double max_time,
                    int min_reg_points,
                    double prob,
                    double precision,
                    bool agglomerateBasedOnCompletions,
                    int agglomeration){
    // structures to store data for validation
    vector<pair<double,double>> confidence_interval_extremes_ResponseTime;
    string ResponseTimeName = "rsp";
    vector<pair<double,double>> confidence_interval_extremes_ActiveTime;
    string ActiveTimeName = "act";

    // run simulation
    System* sys;
    for(int i=0; i<number_of_runs; i++){
        cout << "\nSimulation n. " << i+1 << "\n\n";
        // global time to zero
        clocktime = 0;
        // initialize system using some external function that builds the system
        sys = SystemBuilderFunction();
        // set the preferred regeneration state by picking it from a test run
        sys->setRegenerationState(burn_in_system->getRegenerationState());
        // run with the given parameters
        sys->simulate(max_time, min_reg_points, prob, precision, agglomerateBasedOnCompletions, agglomeration);
        // collect the result as a pair <min,max> which contains (r_hat - Interval/2, r_hat + Interval/2)
        // used for validation
        confidence_interval_extremes_ResponseTime.push_back(sys->getIntervalExtremesResults(ResponseTimeName));
        confidence_interval_extremes_ActiveTime.push_back(sys->getIntervalExtremesResults(ActiveTimeName));
    }
    delete sys;

    // store data for validation
    validation_interval_results Result;
    Result.data[ResponseTimeName] = confidence_interval_extremes_ResponseTime;
    Result.data[ActiveTimeName] = confidence_interval_extremes_ActiveTime;

    return Result;
}

// simple system
System* dummy(){
    // create and initialize stations
    vector<Station*> stations;
    // staz 0 -
    double* params = new double[1]; params[0] = 30;
    Station* zero = new DelayStation(20, 0,RNG::EXP, params);
    stations.push_back(zero);
    // staz 1 -
    params = new double[1]; params[0] = 400;
    Station* one = new ServerStation(0, 1, RNG::EXP, params);
    stations.push_back(one);
//    // staz 2 -
//    params = new double[3];
//    params[0] = 0.8; params[1] = 15; params[2] = 75;
//    Station* two = new SliceStation(0, 2, RNG::HYPEXP, params, 3);
//    stations.push_back(two);

    // glue stations together - set routes
    map<Station*,double> routes;
    // from zero
    routes[one] = 1;
    zero->setRoutes(routes);
    // from one
    routes.clear(); routes[zero] = 1;
    one->setRoutes(routes);
//    // from two
//    routes.clear(); routes[zero] = 1;
//    two->setRoutes(routes);

    // build and return the system object
    // the Future Event List is created inside the System
    System* mysys = new System(stations);

    // WalkStatBalls that watch the system and compute walk times
    // (in our case: Response time...
    WalkStat* ResponseTimeStatBall = new WalkStat("rsp");
    ResponseTimeStatBall->watchSystem(mysys);
    ResponseTimeStatBall->watchFrom(zero);
    ResponseTimeStatBall->watchTo(zero);

    // add them as confidence givers for the system
    mysys->addConfidenceGiver(ResponseTimeStatBall);

    return mysys;
}
// true system
System* createSystem(){
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
    params = new double[1]; params[0] = 210;  // mu
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
    MPDreserve->addUnderControl(swapin);
    MPDreserve->addUnderControl(CPU);
    MPDreserve->addUnderControl(IO1);
    MPDreserve->addUnderControl(IO2);

    // WalkStatBalls that watch the system and compute walk times
    // (in our case: Response time...
    WalkStat* ResponseTimeStatBall = new WalkStat("rsp");
    ResponseTimeStatBall->addStartingPoint(delay);
    ResponseTimeStatBall->watchSystem(mysys);
    ResponseTimeStatBall->watchFrom(delay);
    ResponseTimeStatBall->watchTo(delay);
    // ...and Active time)
    WalkStat* ActiveTimeStatBall = new WalkStat("act");
    ActiveTimeStatBall->addStartingPoint(delay);
    ActiveTimeStatBall->watchSystem(mysys);
    ActiveTimeStatBall->watchFrom(swapin);
    ActiveTimeStatBall->watchTo(delay);
    ActiveTimeStatBall->watchTo(reserve);

    // add them as confidence givers for the system
    mysys->addConfidenceGiver(ResponseTimeStatBall);
    mysys->addConfidenceGiver(ActiveTimeStatBall);

    return mysys;
}
// approximated system
System* approximateSystemNoMPD(){
    // create and initialize stations
    vector<Station*> stations;
    double* params = new double[1];
    // staz 0 - initialized with 20 clients inside
    params[0] = 5000.0;
    Station* delay = new DelayStation(20, 0, RNG::EXP, params);
    stations.push_back(delay);
    // staz 1 - reserve, MPD=10
    // NO MPD IN APPROXIMATED SYSTEM
    // staz 2 - swapin
    params = new double[1]; params[0] = 210;  // mu
    Station* swapin = new ServerStation(0, 2, RNG::EXP, params);
    stations.push_back(swapin);
    // staz 3 - CPU approximately exponential
    params = new double[3]; params[0] = 3;    // mu
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
    // from swapin (2)
    routes.clear(); routes[CPU] = 1;
    swapin->setRoutes(routes);
    // from CPU (3)
    routes.clear();
    routes[CPU] = 0.9; routes[IO1] = 0.065; routes[IO2] = 0.025;
    routes[delay] = 0.01*0.4; routes[swapin] = 0.01*0.6;
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

    // WalkStatBalls that watch the system and compute walk times
    // (in our case: Response time...
    WalkStat* ResponseTimeStatBall = new WalkStat("rsp");
    ResponseTimeStatBall->addStartingPoint(delay);
    ResponseTimeStatBall->watchSystem(mysys);
    ResponseTimeStatBall->watchFrom(delay);
    ResponseTimeStatBall->watchTo(delay);
    // ...and Active time)
    WalkStat* ActiveTimeStatBall = new WalkStat("act");
    ActiveTimeStatBall->addStartingPoint(delay);
    ActiveTimeStatBall->watchSystem(mysys);
    ActiveTimeStatBall->watchFrom(swapin);
    ActiveTimeStatBall->watchTo(delay);
    ActiveTimeStatBall->watchTo(swapin);
    //ActiveTimeStatBall->watchTo(reserve);//NO MPD HERE
    // add them as confidence givers for the system
    mysys->addConfidenceGiver(ResponseTimeStatBall);
    mysys->addConfidenceGiver(ActiveTimeStatBall);

    return mysys;
}
