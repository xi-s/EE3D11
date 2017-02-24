#ifndef BRNEINSTRUCTION_H
#define BRNEINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class BrneInstruction : public Instruction
{
    public:
        using Instruction::Instruction;
        virtual ~BrneInstruction();

        void disassemble();
        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
