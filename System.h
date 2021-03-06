
#ifndef SYSTEM_H
#define SYSTEM_H

#include "Station.h"
#include <vector>
#include <string>
#include "ListManager.h"
#include "GlobalTime.h"
#include "Subject.h"
#include "StatNotifier.h"
#include <set>
#include <map>
#include <utility>
#include "Matrix.h"
#include <iostream>

using std::vector;
using std::string;
using std::set;
using std::map;
using std::pair;
using std::cerr;
using std::cout;

class System : public Subject, public StatNotifier{
private:
    bool engine();                      // simulate one step
    vector<int> initial_state;          // initial values of N for all stations
    vector<Station*> MarkovStations;    // vector of stations with Negative Exponential random engine
    map<string, WalkStat*> confidenceGivers;    // WalkStat objects that can compute confidence intervals
    int _agglomeration;                 // how many regeneration do you want to agglomerate together
    int _agglomeration_count;           // counter for agglomerating cycles
    bool _hit_first_reg;                // hit first regeneration -> after this the true simulation starts
    bool _completionBasedAgglomeration;  // true if you want to agglomerate based on a minimum number of completions. False if you want to agglomerate normally.
public:
    System(vector<Station*> a_stations, map<string,Station*> a_named_stations);

    map<string, Station*> named_stations;
    vector<Station*> stations;
    Dll FEL;
    int reg;            // regeneration cycles
    //bool start_engine;  // true until the simulation starts runs its first engine()
    double Max_Time;    // maximum time after which shut everything down
    int job_number;     // id for jobs/clients' names
    bool first_event;   // false until you create the first event ever
    int Min_Cycles;  // max number of regeneration cycles
    double _confidenceIntervalProbability; // how much probability should the confidence interval(s) cover
    double _confidenceIntervalPrecision;   // how small should the confidence interval be with respect to the value of the estimate
    bool regeneration_testing; // true if you want to make a test run of the system and you want to study the frequency of states
    map< pair<vector<int>,Station*> , unsigned int > states; // map of system states at regeneration points, arrival Markov stations, and relative count of these occurrences
    pair< vector<int>, Station* > regeneration_state; // most frequent 'system state + arrival station' occurring at regeneration points

    Station* operator[](int i);
    Station* operator[](string name);
    void reset();
    bool hitRegeneration(Event& ev); // check for regeneration point
    void simulate(double MaxTime=100000, int MinCycles=10, double confidenceIntervalProbability=0.90, double precision=0.10, bool completionBasedAgglomeration=false, int agglomeration_number=1);
    void generate_event(Station* fr);
    void schedule(Event& ev);   // wrapper for Dll.schedule()
    void dump();
    vector<int> get_state();    // gets the state (N in all stations)
    void addConfidenceGiver(WalkStat* ws);  // sets the confidence giver
    bool reachedConfidence();   // did you reach confidence? if so, you can stop the simulation
    void setRegenerationTesting(bool val); // sets to true or false the regeneration testing run
    void setRegenerationState(pair<vector<int>,Station*> vec); // sets manually the regeneration state
    pair<vector<int>,Station*> getRegenerationState();
    template<int _Stations>
    Matrix<double,_Stations,_Stations> getRoutingMatrix(); // returns a Matrix<double,n,n> Q, with appropriate n, known at runtime
    int getNumberOfStations();  // how many stations in the system?
    pair<double,double> getIntervalExtremesResults(string walkStatName); // returns the couple (r_hat - Interval/2, r_hat + Interval/2), after simulation was run
};

// convert neighbour list to adjacency matrix (Q)
template<int _Stations>
Matrix<double,_Stations,_Stations> System::getRoutingMatrix(){
    const int n = _Stations;
    double** Q = new double*[n];
    map<Station*, double> i_th_route;
    // assign position to stations for fast lookup (below)
    map<Station*,unsigned int> posiz;
    for(unsigned int i=0; i<n; i++){
        // assign the int (position) to a Station*
        posiz[stations[i]] = i;
    }

    // generate routing matrix Q
    for(int i=0; i<n; i++){
        // fills i-th row of Q matrix
        Q[i] = new double[n];
        // initialize to 0 Q entries
        for(int j=0; j<n; j++){
            Q[i][j] = 0;
        }
        // insert non-zero elements where there is a link
        i_th_route = stations[i]->routes;
        for(map<Station*,double>::iterator mit=i_th_route.begin();
            mit!=i_th_route.end(); ++mit){
            Q[i][posiz[(*mit).first]] = (*mit).second;
        }
    }

    // make a Matrix and return it
    Matrix<double,n,n> Qmatrix(Q);
    return Qmatrix;
}

#endif // SYSTEM_H

