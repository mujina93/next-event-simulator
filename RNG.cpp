
#include "DEBUG.h"

#include "RNG.h"
#include "rngs.h"
#include "rvgs.h"
#include <iostream>

using std::cout;

int RNG::counter = 0; // initialization of static counter of RNGs

RNG::RNG(RNG::type typ, double* params):
    streamIndex(RNG::counter++), params(params), typ(typ){
    // if this is the first RNG created ever, initialize the rng library
    if(counter==1)
        PlantSeeds(RNG::seed);
    //DD(fprintf(stderr,"params: %lf\n",params[0]));
}

double RNG::gen(){
    SelectStream(streamIndex);
    switch (typ)
    {
    case EXP:
        return Exponential(params[0]);
        break;
    case HYPEXP:
        return Hyperexponential(params[0],params[1],params[2]);
        break;
    case INST:
        return 0;
        break;
    case UNI:
        return Uniform(0,1);
        break;
    default:
        cout << "Something went wrong with RNG ";
        cout << streamIndex << " " << " of type: " << typ << "\n";
        return -1;
        break;
    }

}
