#ifndef SUBINSTRUCTION_H
#define SUBINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class SubInstruction : public Instruction
{
    public:
        SubInstruction(int, int, int);
        virtual int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
