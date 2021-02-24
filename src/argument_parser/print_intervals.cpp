//
// Created by mhuelsberg on 23.10.20.
//

#include "print_intervals.h"
#include <cmath>

PRINT_INTERVAL::PRINT_INTERVAL(){
}

PRINT_INTERVAL::PRINT_INTERVAL(long* numberOfTimesteps, double* dt, double* oscillationPeriod){
    this->numberOfTimesteps = numberOfTimesteps;
    this->dt = dt;
    this->oscillationPeriod = oscillationPeriod;
}

PRINT_INTERVAL& PRINT_INTERVAL::update(const PRINT_INTERVAL& other){
    if(other.interval != 0){
        interval = other.interval;
        duration = 0;
        period = 0;
    }
    if(other.duration != 0){
        duration = other.duration;
        period = 0;
    }
    if(other.period != 0) period = other.period;
    return *this;
}

PRINT_INTERVAL& PRINT_INTERVAL::finalize(){
    finalized = true;   // needs to be at beginning because setDuration/setPeriod question this
    if(duration != 0){
        setDuration(duration);
        duration = 0;
    }
    if(period != 0){
        setPeriod(period);
        period = 0;
    }
    return *this;
}

double PRINT_INTERVAL::getDuration() const{
    if(duration == 0){
        return double(interval) * *dt;
    }
    else return duration;
}

double PRINT_INTERVAL::getPeriod() const{
    if(period == 0){
        return double(interval) * *dt / *oscillationPeriod;
    }
    else{
        return period;
    }
}

bool PRINT_INTERVAL::isFinalized() const{
    return finalized;
}

PRINT_INTERVAL& PRINT_INTERVAL::setDuration(double duration){
    if(finalized){
        interval = round(duration / *dt);
    }
    else{
        this->duration = duration;
    }
    return *this;
}

PRINT_INTERVAL& PRINT_INTERVAL::setPeriod(double period){
    if(finalized){
        interval = round(period * *oscillationPeriod / *dt);
    }
    else{
        this->period = period;
    }
    return *this;
}

PRINT_INTERVAL::operator int() const{
    return interval;
}

PRINT_INTERVAL& PRINT_INTERVAL::operator=(double interval){
    this->interval = interval;
    return *this;
}
