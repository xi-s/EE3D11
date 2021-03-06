#include <iostream>
#include <math.h>

#include "computer.h"

using namespace std;

Computer::Computer(){
}

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
    cout << endl << "====Computer Stats===="    << endl;
    cout << "Clock Rate (GHz):\t"	    << m_clockRateGHz << endl;
    cout << "CPI Arith:\t\t"		    << m_cpiArith << endl;
    cout << "CPI Store:\t\t"		    << m_cpiStore << endl;
    cout << "CPI Load:\t\t"		        << m_cpiLoad << endl;
    cout << "CPI Branch:\t\t"		    << m_cpiBranch << endl;
    cout << "-------------------------"	<< endl;
    cout << "Global CPI:\t\t"		    << calculateGlobalCPI() << endl;
    cout << "Global MIPS:\t\t"		    << calculateGlobalMIPS() << endl;
    cout  << endl;
}

double Computer::calculateGlobalCPI(){
    double globalCPI = (m_cpiArith + m_cpiStore + m_cpiLoad + m_cpiBranch) / 4;
    return globalCPI;
}

double Computer::calculateWeightedCPI(Program &program){
  /*
    sum(Ic * CPIc) / I
    Ic: Total instructions per class
    CPI: CPI per class
    I: Total instructions per program

    Accumulating the calculations per instruction class,
    divided by the total number of instructions
    yields a weighted CPI.
  */
  double weightedCPI =  (program.getNumArith() * m_cpiArith)    +
                        (program.getNumStore() * m_cpiStore)    +
                        (program.getNumBranch() * m_cpiBranch)  +
                        (program.getNumLoad() * m_cpiLoad);
  return weightedCPI / program.getTotal();
}

double Computer::calculateMIPS(Program &program){
    // F / (CPI * 10e6)
    double MIPS = (m_clockRateGHz * 10e9) / (calculateWeightedCPI(program) * 10e6);
    cout << "\tMIPS: " << MIPS << endl;
    return MIPS;
}

double Computer::calculateExecutionTime(Program &program){
    // T = (I * CPI)/ F;
    double executionTime = (program.getTotal() * calculateWeightedCPI(program) )/((m_clockRateGHz) *  10e9);
    cout << "\tExecution time (sec): " << executionTime << endl;
    return executionTime;
}

double Computer::calculateGlobalMIPS(){
    // F / (CPI * 10e6)
    double globalMIPS = (m_clockRateGHz * 10e9) / (calculateGlobalCPI() * 10e6);
    return globalMIPS;
}

void Computer::load(Program* programs){
    for(int i = 0; i < 3; i++){
        cout << "Program " << i << ": " << endl;
        calculateExecutionTime(programs[i]);
        calculateMIPS(programs[i]);
    }
}
