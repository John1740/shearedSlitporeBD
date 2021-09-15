//
// Created by mhuels on 4/15/20.
//

#include "clock.h"
#include <iomanip>
#include <cmath>
#include <algorithm>    //needed for count (in strings)

CLOCK::CLOCK(){
    reset();
}

void CLOCK::reset(){
    timePoints.clear();
    clockTicks.clear();
    length = timePoints.size();
    lap();
}

int CLOCK::lap(){
    timePoints.push_back(time(0));
    clockTicks.push_back(clock());
    return length++;
}

time_t CLOCK::getTimePoint(int i){
    return timePoints.at2(i);
}

clock_t CLOCK::getClockTick(int i){
    return clockTicks.at2(i);
}

string CLOCK::readTimePoint(int i, const char* fmt){
    tm* timeStructure = localtime(&timePoints.at2(i));
    stringstream ss;
    ss << put_time(timeStructure, fmt);
    return ss.str();
}

double CLOCK::getDuration(int i, int j, bool walltime){
    double duration;
    if(walltime){
        duration = timePoints.at2(j) - timePoints.at2(i);
    }
    else{
        duration = double(clockTicks.at2(j) - clockTicks.at2(i)) / CLOCKS_PER_SEC;
    }
    return duration;
}

string CLOCK::readDuration(int i, int j, bool walltime, const char* format){
    double seconds = getDuration(i, j, walltime);
    int minutes = seconds / 60;
    int hours = minutes / 60;
    int days = hours / 24;
    stringstream ss;
    char buffer[50];    //should be large enough in all cases, can be optimized
    string s = string(format);
    int numberOfPercentSigns = count(s.begin(), s.end(), '%');
    if(numberOfPercentSigns > 4 || numberOfPercentSigns <= 0){
        throw invalid_argument("readDuration format expects 1-4 percent signs ('%')!");
    }
    else if(numberOfPercentSigns == 4){
        sprintf(buffer, format, days, hours % 24, minutes % 60, fmod(seconds, 60.0));
    }
    else if(numberOfPercentSigns == 3){
        sprintf(buffer, format, hours, minutes % 60, fmod(seconds, 60));
    }
    else if(numberOfPercentSigns == 2){
        sprintf(buffer, format, minutes, fmod(seconds, 60));
    }
    else if(numberOfPercentSigns == 1){
        sprintf(buffer, format, seconds);
    }
    ss << buffer;
    return ss.str();
}

double CLOCK::operator()(int j, bool walltime){
    double duration;
    if(walltime){
        duration = time(0) - timePoints.at2(j);
    }
    else{
        clock_t now = clock();
        duration = double(now - clockTicks.at2(j)) / CLOCKS_PER_SEC;
    }
    return duration;
}

string CLOCK::operator()(const char* fmt){
    time_t t = time(0);
    tm* timeStructure = localtime(&t);
    stringstream ss;
    ss << put_time(timeStructure, fmt);
    return ss.str();
}

double CLOCK::operator()(int i, int j, bool walltime){
    return getDuration(i, j, walltime);
}

string CLOCK::operator[](int i){
    return readTimePoint(i);
}
