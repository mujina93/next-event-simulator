
#include "Estimator.h"
#include <boost/math/distributions/normal.hpp>

///--- Estimtor ---
bool Estimator::satisfiesPrecision(double precision){
    return (interval.value < precision*estimate);
}

void Estimator::setInterval(double a_interval_length, double a_probability){
    interval.value = a_interval_length;
    interval.probability = a_probability;
}

void Estimator::setEstimate(double value){
    estimate = value;
}

///--- StdNormEstimator ---
double StdNormEstimator::quantile(double p){
    boost::math::normal standard_normal(0.0, 1.0);
    // 'p' of distribution is below q
    // (e.g. p=0.95 means 95% of the distribution is below q)
    return boost::math::quantile(standard_normal, p);
}

double StdNormEstimator::quantile2tailed(double p){
    boost::math::normal standard_normal(0.0, 1.0);
    // 'p' of distribution is between -q and q
    // (e.g. p=0.95 means 95% of the distribution is between -q and q)
    return boost::math::quantile(standard_normal, 0.5 + p/2);
}
