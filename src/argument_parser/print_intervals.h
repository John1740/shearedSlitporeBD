//
// Created by mhuelsberg on 29.09.20.
//

#ifndef SHEAREDSLITPOREBD_PRINT_INTERVALS_H
#define SHEAREDSLITPOREBD_PRINT_INTERVALS_H

class PRINT_INTERVAL{
private:
    int* numberOfTimesteps;
    double* dt;
    double* oscillationPeriod;
    int interval = 0;
    double duration = 0;
    double period = 0;
    bool finalized = false;
public:
    // constructors
    PRINT_INTERVAL();
    PRINT_INTERVAL(int* numberOfTimesteps, double* dt, double* oscillationPeriod);

    // update with other instance of this class
    PRINT_INTERVAL& update(const PRINT_INTERVAL& other);

    // choose the prioritized print intervals
    PRINT_INTERVAL& finalize();

    // getter
    double getDuration() const;
    double getPeriod() const;
    bool isFinalized() const;

    // setter
    PRINT_INTERVAL& setDuration(double duration);
    PRINT_INTERVAL& setPeriod(double period);

    // operators
    operator int() const;
    PRINT_INTERVAL& operator=(double interval);
};

#endif //SHEAREDSLITPOREBD_PRINT_INTERVALS_H
