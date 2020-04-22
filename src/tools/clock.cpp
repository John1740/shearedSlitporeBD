//
// Created by mhuels on 4/15/20.
//

#include "clock.h"

CLOCK::CLOCK() {
    reset();
}

void CLOCK::reset() {
    timePoints.clear();
    clockTimes.clear();
    length = timePoints.size();
    addTimePoint();
}

int CLOCK::addTimePoint() {
    timePoints.push_back(time(0));
    clockTimes.push_back(clock());
    return length++;
}

time_t CLOCK::getTimePoint(int i) {
    return timePoints.at2(i);
}

clock_t CLOCK::getClockTime(int i) {
    return clockTimes.at2(i);
}

string CLOCK::readTimePoint(int i, const char* fmt) {
    tm* timeStructure = localtime(&timePoints.at2(i));
    stringstream ss;
    ss << put_time(timeStructure, fmt);
    return ss.str();
}

double CLOCK::getDuration(int i, int j) {
    double duration = double(clockTimes.at2(j) - clockTimes.at2(i)) / CLOCKS_PER_SEC;
    return duration;
}

string CLOCK::readDuration(int i, int j, const char* format) {
    double seconds = getDuration(i, j);
    int minutes = seconds/60;
    int hours = minutes/60;
    int days = hours/24;
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