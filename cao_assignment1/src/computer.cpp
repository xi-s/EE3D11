#include <iostream>

#include "computer.h"

using namespace std;

Computer::Computer(double clockRateGHz, double cpiArith, double cpiStore, double cpiLoad, double cpiBranch)
{
    //ctor
    m_clockRateGHz = clockRateGHz;
    m_cpiArith = cpiArith;
    m_cpiStore = cpiStore;
    m_cpiLoad = cpiLoad;
    m_cpiBranch = cpiBranch;
}

void Computer::printStats(){
    cout << "====Computer Stats===="	<< endl;
    cout << "Clock Rate (GHz):\t"	<< m_clockRateGHz << endl;
    cout << "CPI Arith:\t\t"		<< m_cpiArith << endl;
    cout << "CPI Store:\t\t"		<< m_cpiStore << endl;
    cout << "CPI Load:\t\t"		<< m_cpiLoad << endl;
    cout << "CPI Branch:\t\t"		<< m_cpiBranch << endl;
}


