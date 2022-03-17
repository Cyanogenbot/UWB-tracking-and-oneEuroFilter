#include "Arduino.h"
#include "oneEuroFilter.h"

oneEuroFilter::oneEuroFilter(float xZeroIn, float dxZeroIn, float minCutoffIn, float betaIn, float deltaCutoffIn)
{
    timeZero = millis();
    xZero = xZeroIn;
    dxZero = dxZeroIn;
    minCutoff = minCutoffIn;
    beta = betaIn;
    deltaCutoff = deltaCutoffIn;
}

float oneEuroFilter::filter(float timeNew, float xNew){
    float deltaTime = timeNew - timeZero;
    float deltaAlpha = smoothFactor(deltaTime, deltaCutoff);
    float deltaX = (xNew-xZero) / deltaTime;
    float deltaNew = exponentialSmoothing(deltaAlpha, deltaX, dxZero);

    float cutoff = minCutoff + beta * abs(deltaNew);
    float alpha = smoothFactor(deltaTime, cutoff);
    float xModified = exponentialSmoothing(alpha, xNew, xZero);

    xZero = xModified;
    dxZero = deltaNew;
    timeZero = timeNew;
}

float smoothFactor(float deltaTime, float cutoff){
    float r = 2 * PI * cutoff * deltaTime;
    return (r / (r+1));

}
float exponentialSmoothing(float alpha, float x, float x_prev){
    return (alpha * x + (1- alpha)* x_prev);
}