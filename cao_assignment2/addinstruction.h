#ifndef ADDINSTRUCTION_H
#define ADDINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class AddInstruction : public Instruction
{
    public:
        AddInstruction(int, int, int);
        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
