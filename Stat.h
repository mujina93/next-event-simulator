
#ifndef STAT_H
#define STAT_H

class StatBall{
public:
    StatBall();
    double sum;
    double sumSq;
    double Size;

    enum staType {          // acronyms for statistics that a StatBall may compute
        AVG, M2, UVAR, SVAR, CV2, CV
    };

    void updateStat(double new_y, double new_x);  // add new observations
    double digest(StatBall::staType what);        // compute statistics
};

#endif // STAT_H

