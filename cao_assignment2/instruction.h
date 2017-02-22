#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include "registers.h"

using namespace std;

class Instruction
{
private:


    // Instruction parameters
    int rs; // source 1
    int rt; // source 2
    int rd; // destination


public:
    Instruction(int rd, int rs, int rt);
    virtual void dissassemble();
    virtual int execute(Registers *);
};

#endif /* _INSTRUCTION_H_ */
