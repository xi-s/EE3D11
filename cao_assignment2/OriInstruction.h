#ifndef ORIINSTRUCTION_H
#define ORIINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class OriInstruction : public Instruction
{
    public:
        OriInstruction(int, int, int);
        virtual ~OriInstruction();

        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
