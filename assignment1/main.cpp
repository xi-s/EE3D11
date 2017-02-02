#include <iostream>

#include "computer.h"
#include "program.h"

using namespace std;

int main()
{
    Computer computer(1.0,2,3,4,5);
    computer.printStats();

    Program program(5,4,3,2,1);
    program.printStats();
    return 0;
}
