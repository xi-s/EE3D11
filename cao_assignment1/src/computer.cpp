#include <iostream>
#include <math.h>

#include "computer.h"

using namespace std;

Computer::Computer( double clockRateGHz,
                    double cpiArith,
                    double cpiStore,
                    double cpiLoad,
                    double cpiBranch){

    m_clockRateGHz = clockRateGHz;
    m_cpiArith = cpiArith;
    m_cpiStore = cpiStore;
    m_cpiLoad = cpiLoad;
    m_cpiBranch = cpiBranch;
}

void Computer::printStats()
{
    cout << "====Computer Stats===="    << endl;
    cout << "Clock Rate (GHz):\t"	    << m_clockRateGHz << endl;
    cout << "CPI Arith:\t\t"		    << m_cpiArith << endl;
    cout << "CPI Store:\t\t"		    << m_cpiStore << endl;
    cout << "CPI Load:\t\t"		        << m_cpiLoad << endl;
    cout << "CPI Branch:\t\t"		    << m_cpiBranch << endl;
    cout << "-------------------------"	<< endl;
    cout << "Global CPI:\t\t"		    << calculateGlobalCPI() << endl << endl;
}

double Computer::calculateGlobalCPI(){
    double globalCPI = (m_cpiArith + m_cpiStore + m_cpiLoad + m_cpiBranch) / 4;
    return globalCPI;
}

double Computer::calculateExecutionTime(Program program){
    // T = (I * CPI)/ F;
    double executionTime = (program.getTotal() * calculateGlobalCPI() )/((this->m_clockRateGHz) *  pow(10, 9));
    cout << "Execution time (sec): " << executionTime << endl;
    return executionTime;
}

double Computer::calculateMIPS(Program program){
    // MIPS = I / (T * 10^6);
    double MIPS = program.getTotal() / ((calculateExecutionTime(program) * pow(10, 6)));
    cout << "MIPS: " << MIPS << endl;
    return MIPS;
}
