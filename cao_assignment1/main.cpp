#include <iostream>

#include "computer.h"
#include "program.h"

using namespace std;

int main(){

    Program programA(2000, 100, 100, 50);
    programA.printStats();

    Program programB(2000, 0.1f, 0.4f,  0.25f);
    programB.printStats();

    Program programC(500, 100, 2000, 200);
    programC.printStats();

    Computer computer1(1.0, 2.0, 2.0, 3.0, 4.0);
    computer1.printStats();
    cout << "Program A: " << endl;
    computer1.calculateExecutionTime(programA);
    computer1.calculateMIPS(programA);
    cout << "Program B: " << endl;
    computer1.calculateExecutionTime(programB);
    computer1.calculateMIPS(programB);
    cout << "Program C: " << endl;
    computer1.calculateExecutionTime(programC);
    computer1.calculateMIPS(programC);

    Computer computer2(1.2, 2.0, 3.0, 4.0, 3.0);
    computer2.printStats();
    cout << "Program A: " << endl;
    computer2.calculateExecutionTime(programA);
    computer2.calculateMIPS(programA);
    cout << "Program B: " << endl;
    computer2.calculateExecutionTime(programB);
    computer2.calculateMIPS(programB);
    cout << "Program C: " << endl;
    computer2.calculateExecutionTime(programC);
    computer2.calculateMIPS(programC);

    Computer computer3(2.0, 2.0, 2.0, 4.0, 6.0);
    computer3.printStats();
    cout << "Program A: " << endl;
    computer3.calculateExecutionTime(programA);
    computer3.calculateMIPS(programA);
    cout << "Program B: " << endl;
    computer3.calculateExecutionTime(programB);
    computer3.calculateMIPS(programB);
    cout << "Program C: " << endl;
    computer3.calculateExecutionTime(programC);
    computer3.calculateMIPS(programC);

    return 0;
}
