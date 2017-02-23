#include <iostream>

#include "program.h"

using namespace std;

Program::Program(int numArith, int numStore, int numLoad, int numBranch)
{
    m_numArith	= numArith;
    m_numStore	= numStore;
    m_numLoad	= numLoad;
    m_numBranch	= numBranch;
    m_numTotal	= numArith + numStore + numLoad + numBranch;
}

// Overloaded constructor for fractions
Program::Program(int numTotal, double numArith, double numStore, double numLoad)
{
    m_numArith	= numArith * numTotal;
    m_numStore	= numStore * numTotal;
    m_numLoad	= numLoad * numTotal;
    m_numTotal	= numTotal;

    // Number of Branch instructions calculated from known variables
    m_numBranch = numTotal - ((numArith + numStore + numLoad) * numTotal);
}

void Program::printStats(){
    cout << "====Program Stats===="	    << endl;
    cout << "Arithmetic operations:\t"  << m_numArith << endl;
    cout << "Store operations:\t"       << m_numStore << endl;
    cout << "Load operations:\t"        << m_numLoad << endl;
    cout << "Branch operations:\t"      << m_numBranch << endl;
    cout << "-------------------------"	<< endl;
    cout << "Total operations:\t"       << m_numTotal << endl << endl;
}

