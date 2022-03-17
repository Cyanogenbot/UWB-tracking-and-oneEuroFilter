#ifndef oneEuroFilter_h
#define oneEuroFilter_h

#include "Arduino.h"

class oneEuroFilter
{
private:
    float timeZero;
    float xZero;
    float dxZero;
    float minCutoff;
    float beta;
    float deltaCutoff;
    float smoothFactor(float deltaTime, float cutoff);
    float exponentialSmoothing(float alpha, float x, float x_prev);
    unsigned long millis();
public:
    oneEuroFilter(float xZero, float dxZero, float minCutoff, float beta, float deltaCutoff);
    float filter(float timeNew, float xNew);
};
#endif


