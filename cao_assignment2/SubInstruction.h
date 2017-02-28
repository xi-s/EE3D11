#ifndef SUBINSTRUCTION_H
#define SUBINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class SubInstruction : public Instruction
{
    public:
        using Instruction::Instruction;
        virtual ~SubInstruction();

        void disassemble();
        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
