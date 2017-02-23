#ifndef BRNEINSTRUCTION_H
#define BRNEINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class BrneInstruction : public Instruction
{
    public:
        BrneInstruction(int, int, int);
        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
