#include <iostream>

#include "computer.h"
#include "program.h"

using namespace std;

int main(){

    Computer computer1(1.0, 2.0, 2.0, 3.0, 4.0);
    computer1.printStats();

    Computer computer2(1.2, 2.0, 3.0, 4.0, 3.0);
    computer2.printStats();

    Computer computer3(2.0, 2.0, 2.0, 4.0, 6.0);
    computer3.printStats();

    Program programA(2000, 100, 100, 50);
    programA.printStats();

    Program programB(2000, 0.1, 0.4,  0.25);
    programB.printStats();

    Program programC(500, 100, 2000, 200);
    programC.printStats();

    //computer3.calculateExecutionTime(program1);
    computer1.calculateMIPS(programA);
    return 0;
}
