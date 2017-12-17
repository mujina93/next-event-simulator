
#ifndef RNG_H
#define RNG_H

class RNG{
private:
    static int counter; // total RNGs created. Avoids collisions in setting the stream indexes
    static const long seed = 1234567890;  // initial seed for rngs library
public:
    enum type {
        INST, EXP, HYPEXP, UNI
    };
    // constructor with variable number of arguments for distribution's parameters
    RNG(RNG::type typ, double* params);

    int streamIndex;
    double* params;
    RNG::type typ;

    double gen();
};

#endif // RNG_H

