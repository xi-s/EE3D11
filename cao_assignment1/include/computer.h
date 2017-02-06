#ifndef COMPUTER_H_INCLUDED
#define COMPUTER_H_INCLUDED

#include "program.h"

class Computer{
    private:
        double m_clockRateGHz;
        // CPI per each instruction class
        double m_cpiArith;
        double m_cpiStore;
        double m_cpiLoad;
        double m_cpiBranch;
    public:
        // Constructor prototype
        Computer(double, double, double, double, double);

        void printStats();
        double calculateGlobalCPI();
        double calculateExecutionTime(Program);
        double calculateMIPS(Program);
};


#endif // COMPUTER_H_INCLUDED
