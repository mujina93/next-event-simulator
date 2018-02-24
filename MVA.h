
#ifndef MVA_H
#define MVA_H

#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include "Station.h"
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"
#include <utility>
#include <sstream>
#include "System.h"
#include <stdexcept>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::pair;

template<typename _Scalar, int _Stations, int _Clients>
class MVA{
public:
    MVA(const Matrix<_Scalar,_Stations,_Stations>& routingMatrix,
        const vector<Station::StationType>& station_types,
        const vector<double>& service_or_delay_times);
    MVA(System* sys, vector<int> active_stations = {});

    Matrix<_Scalar,_Stations,_Clients> avg_n;  //expected queue lengths
    Matrix<_Scalar,_Stations,_Clients> avg_w;  //expected waiting times
    Matrix<_Scalar,_Stations,_Clients> X;      //throughtputs
    Matrix<_Scalar,_Stations,_Clients> U;      //utilizations
    vector<_Scalar> S;     //service times for LI stations and delay times for D stations
    vector<_Scalar> V;              //visiting counts
    vector<_Scalar> R;              //response times as function of number of clients
    vector<_Scalar> A;              // active times as function of number of clients
    Matrix<_Scalar,_Stations,_Stations> Q;      //routing matrix
    vector<Station::StationType> _station_types;//station types
    int bottleneckStation;      // index of bottleneck stations
    vector<int> _active_stations;    // indexes of stations that form the active part of the system

    void bottleneckAnalysis();
    void MVA_LI_D();         // always run after bottleneckAnalysis()
    void print_results();
    void plot_results();
    void plot_vector(vector<_Scalar> ydata, string ylabel="", string title="default", string curve="");
    pair<_Scalar,_Scalar> getResponseTime_ActiveTime(int number_of_clients);
};

// build an MVA by giving in a squared routing matrix Q of the system
// and the vector of the station types
template<typename _Scalar, int _Stations, int _Clients>
MVA<_Scalar,_Stations,_Clients>::MVA(
        const Matrix<_Scalar,_Stations,_Stations>& routingMatrix,
        const vector<Station::StationType>& station_types,
        const vector<double>& service_or_delay_times){
    Q = routingMatrix;
    _station_types = station_types;
    for(int i=0; i<_Stations; i++){
        S.push_back(service_or_delay_times[i]);
        // initialize to 0
        V.push_back(0);
    }
    for(int k=0; k<_Clients; k++){
        R.push_back(0);
        A.push_back(0);
    }
}

// construct taking data from a System
template<typename _Scalar, int _Stations, int _Clients>
MVA<_Scalar,_Stations,_Clients>::MVA(System* sys, vector<int> active_stations){
    if(_Stations!=sys->getNumberOfStations()){
        throw std::runtime_error("wrong number of stations in MVA constructor (template parameter)");
    }
    Q = sys->getRoutingMatrix<_Stations>();
    cout << "routing matrix for the system:\n";
    Q.dump(3);
    for(int i=0; i<_Stations; i++){
        _station_types.push_back(sys->stations[i]->getType());
        S.push_back(sys->stations[i]->getTypicalTime());
        // initialize to 0
        V.push_back(0);
    }
    for(int k=0; k<_Clients; k++){
        R.push_back(0);
        A.push_back(0);
    }
    for(vector<int>::iterator it=active_stations.begin(); it!=active_stations.end(); ++it){
        _active_stations.push_back(*it);
    }
}

// compute visiting counts and find bottleneck station
template<typename _Scalar, int _Stations, int _Clients>
void MVA<_Scalar,_Stations,_Clients>::bottleneckAnalysis(){
    V = Q.leftPerron().to_Vector();
    // NORMALIZE WITH RESPECT TO STATION 1 (SWAPIN)
    /*
    if(V[1]!=0){
        _Scalar norm = V[1];
        for(unsigned int i=0;i<V.size();i++){
            V[i]/=norm;
        }
    } else {
        cout << "V[1] != 0. Result is not normalized\n";
    }
    */
    vector<_Scalar> D;
    for(unsigned int i=0; i<V.size(); i++){
        if(_station_types[i]==Station::D){
            D.push_back(0.0);
        } else {
            D.push_back(V[i]*S[i]);
        }
    }
    cout << "\nBOTTLENECK ANALYSIS\n";
    cout << "Visiting counts\n";
    typename vector<_Scalar>::iterator it;
    for(it=V.begin(); it!=V.end(); ++it){
        cout << *it << " " ;
    }
    cout << "\n";
    cout << "D's\n";
    for(it=D.begin(); it!=D.end(); ++it){
        cout << *it << " " ;
    }
    bottleneckStation = std::distance(D.begin(),
                                std::max_element(D.begin(),D.end()));
    cout << "\nBottleneck station: " << bottleneckStation << " (MVA index)\n";
}

// find all statistics
template<typename _Scalar, int _Stations, int _Clients>
void MVA<_Scalar,_Stations,_Clients>::MVA_LI_D(){
    // normalization constant for computing active time
    _Scalar norm = 1;//V[1];
    // computing statistics
    for(int k=0; k<_Clients; k++){      // k stands for k+1 clients
        for(int i=0; i<_Stations; i++){ // stations indexing starts from 0
            if(_station_types[i] == Station::D){
                avg_w[i][k] = S[i];
            }else{
                avg_w[i][k] = S[i]*(1+avg_n[i][k-1]);
            }
        }
        double sum = 0.0;
        for(int i=0; i<_Stations; i++){
            sum += V[i]*avg_w[i][k];
        }
        X[0][k] = double(k+1)/sum;
        for(int i=0; i<_Stations; i++){
            X[i][k] = V[i]*X[0][k];
            if(_station_types[i] == Station::D){
                avg_n[i][k] = S[i]*X[i][k];
                U[i][k] = avg_n[i][k]/double(k+1);
            }else{
                U[i][k] = S[i]*X[i][k];
                avg_n[i][k] = U[i][k]*(1+avg_n[i][k-1]);
            }
        }
        //! ASSUMING DELAY STATION IS AT INDEX 0
        R[k]=double(k+1)/X[0][k] - S[0];

        // active time (average time spent in active part of the system)
        for(vector<int>::iterator it = _active_stations.begin(); it != _active_stations.end(); ++it){
            A[k] += V[*it]/norm*avg_w[*it][k];
        }
    }
}

// prints statistics
template<typename _Scalar, int _Stations, int _Clients>
void MVA<_Scalar,_Stations,_Clients>::print_results(){
    cout << "MVA results\n";
    cout << "S (or Z)\n";
    Matrix<_Scalar,_Stations,1> mat_vecS(S);
    mat_vecS.transpose().dump();

    cout << "V\n";
    Matrix<_Scalar,_Stations,1> mat_vecV(V);
    mat_vecV.transpose().dump();

    cout << "avg n\n";
    avg_n.dump();

    cout << "avg w\n";
    avg_w.dump();

    cout << "X\n";
    X.dump(10);

    cout << "U\n";
    U.dump();

    cout << "R\n";
    Matrix<_Scalar,_Clients,1> mat_vecR(R);
    mat_vecR.transpose().dump();

    cout << "Active time\n";
    Matrix<_Scalar,_Clients,1> mat_vecA(A);
    mat_vecA.transpose().dump();
}

// string curve can be an expression like "5" or "5*x - 10", any
// valid text for a function in gnuplot
template<typename _Scalar, int _Stations, int _Clients>
void MVA<_Scalar,_Stations,_Clients>::plot_vector(vector<_Scalar> ydata, string ylabel, string title, string curve){
    Gnuplot gp;
    gp << "set term png size 600, 400\n";
    gp << "set output '" << title << ".png'\n";
    vector<double> xdata(ydata.size());
    std::iota(xdata.begin(), xdata.end(), 1);   // requires c++11

    std::ostringstream strs;
    strs << *max_element(ydata.begin(),ydata.end())*1.05;
    string y_limit = strs.str();
    if(curve!=""){
        string curve_function = "f(x) = " + curve; //define asymptote
        gp << curve_function << "\n";
    }
    gp << "set yrange [0:" << y_limit << "]\n";
    gp << "set ylabel '" << ylabel << "'\n" << "set xlabel 'clients'\n";
    gp << "plot '-' with points title '" << title << "'";
    if(curve!=""){
        gp << ", f(x) with lines";
    }
    gp << "\n";
    pair<vector<double>,vector<double>> D = make_pair(xdata,ydata);
    gp.send1d(D);
    gp << "set output\n";
}

template<typename _Scalar, int _Stations, int _Clients>
void MVA<_Scalar,_Stations,_Clients>::plot_results(){
    // plot response time
    plot_vector(R,"R","response-time");
    // plot active time
    plot_vector(A, "A", "active-time");
    // plot average n for each station
    vector<_Scalar> avg_n_VEC;
    std::ostringstream stringStream;
    for(int i=0; i<_Stations; i++){
        avg_n_VEC.assign(avg_n[i],avg_n[i]+_Clients);
        stringStream << "avg-n-station-";
        stringStream << i;
        plot_vector(avg_n_VEC,"avg n",stringStream.str());
        stringStream.str("");
        stringStream.clear();
    }
}

template<typename _Scalar, int _Stations, int _Clients>
pair<_Scalar,_Scalar> MVA<_Scalar,_Stations,_Clients>::getResponseTime_ActiveTime(int number_of_clients){
    pair<_Scalar,_Scalar> results(R[number_of_clients-1], A[number_of_clients-1]);
    return results;
}

#endif // MVA_H

