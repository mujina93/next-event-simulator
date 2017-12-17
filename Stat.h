
#ifndef STAT_H
#define STAT_H

class StatBall{
public:
    StatBall();
    double sum;
    double sumSq;
    double Size;

    enum staType {
        AVG, M2, UVAR, SVAR, CV2, CV
    };

    void update(double new_y, double new_x);
    double digest(StatBall::staType what);
};

#endif // STAT_H

