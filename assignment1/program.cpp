#include <iostream>

#include "program.h"

using namespace std;

Program::Program(int numArith, int numStore, int numLoad, int numBranch, int numTotal)
{
    //ctor
    m_numArith	= numArith;
    m_numStore	= numStore;
    m_numLoad	= numLoad;
    m_numBranch	= numBranch;
    m_numTotal	= numTotal;
}

void Program::printStats(){
    cout << "====Program Stats===="	<< endl;
    cout << "Arithmetic operations:\t" << m_numArith << endl;
    cout << "Store operations:\t" << m_numStore << endl;
    cout << "Load operations:\t" << m_numLoad << endl;
    cout << "Branch operations:\t" << m_numBranch << endl;
    cout << "Total operations:\t" << m_numTotal << endl;
}
