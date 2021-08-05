//
// Created by mhuels on 4/15/20.
//

#ifndef SHEAREDSLITPOREBD_CLOCK_H
#define SHEAREDSLITPOREBD_CLOCK_H

#include <time.h>
#include "my_vector.h"
#include <string>

using namespace std;

class CLOCK{
private:
    //contains time points generated via time(0)
    my_vector<time_t> timePoints;
    //contains clock times generated via clock(), needs to be converted to seconds
    my_vector<clock_t> clockTimes;
    int length;

public:
    CLOCK();
    //adds an initial timePoint (index=0)
    void reset();

    //returns the index of the added timePoint
    int addTimePoint();

    time_t getTimePoint(int i);
    clock_t getClockTime(int i);

    //formatting of <iomanip> put_time is used
    //check https://en.cppreference.com/w/cpp/io/manip/put_time
    string readTimePoint(int i, const char* fmt = "%F %T");

    //return duration between timePoints i and j in seconds
    //examples: duration(0, -1) returns duration between first and last call of addTimePoint()
    double getDuration(int i, int j);

    //return duration between timePoints i and j as a formatted string
    //formatting follows printf-norms. number of '%' determines output:
    //one   '%' -> print seconds (double)
    //two   '%' -> print minutes (int) and seconds (double)
    //three '%' -> print hours (int), minutes (int) and seconds (double)
    //four  '%' -> print days (int), hours (int), minutes (int) and seconds (double)
    string readDuration(int i, int j, const char* format = "%d days %02d:%02d:%06.3f");

    //overload operator[] to get timePoints
    double operator()(int j);
    string operator()(const char* fmt="%F %T");
    double operator()(int i, int j);
    string operator[](int i);
};

#endif //SHEAREDSLITPOREBD_CLOCK_H
