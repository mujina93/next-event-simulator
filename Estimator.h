
#ifndef ESTIMATOR_H
#define ESTIMATOR_H

class Estimator{
public:
    // confidence interval struct
    // using a struct since the confidence interval is actually an
    // entwined couple: an interval length, and a probability
    struct confidence_interval{
        double value;       // length of interval
        double probability; // how much probability is this covering
    };

    double estimate;                  // point estimate
    confidence_interval interval;     // confidence interval on the estimate
    //double precision;               // how much precise should the estimate be

    bool satisfiesPrecision(double precision);
    void setEstimate(double value);
    void setInterval(double a_interval_length, double a_probability);
    virtual double quantile(double p) =0;  // returns the quantile associated to the given probability, based on the distribution of your object
    virtual double quantile2tailed(double p) =0; // q such that there is p prob. between -q and q
};

// estimator in the case in which the variable is assumed to be
// distributed as a standard normal N(0,1)
class StdNormEstimator : public Estimator {
public:
    double quantile(double p) override; // implementation of quantile() for standar normal
    double quantile2tailed(double p) override;
};

#endif // ESTIMATOR_H
