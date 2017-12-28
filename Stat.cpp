
#include "Stat.h"
#include <cmath>
#include <cstdio>

StatBall::StatBall() : sum(0), sumSq(0), Size(0) {
}

void StatBall::updateStat(double new_y, double new_x){
    sum = sum + new_y*new_x;  // the product by new_x is here for the cases in which X is non discrete and new_x is != 1
    sumSq = sumSq + new_y*new_y*new_x; // the product by new_x is here for the cases in which X is non discrete and new_x is != 1
    Size = Size + new_x;
}

double StatBall::digest(StatBall::staType what){
    switch(what){
        case AVG: // average
            return sum/Size;
        case M2: // second moment
            return sumSq/Size;
        case UVAR: // uncorrected variance = E[X^2] - (E[X]^2)
            return (sumSq - (sum)*(sum/Size))/Size;
        case SVAR: // corrected variance = (n/(n-1))*uvar - only when Size is integer!
            return (sumSq - (sum)*(sum/Size))/(Size-1);
        case CV2: // coefficient of variation squared = svar/M2
            return (sumSq - (sum)*(sum/Size)) / ((Size-1) * (sumSq/Size));
        case CV: // coefficient of variation
            return sqrt((sumSq - (sum)*(sum/Size)) / ((Size-1) * (sumSq/Size)));
    }
    return sum/Size;
}
