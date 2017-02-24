#ifndef ADDINSTRUCTION_H
#define ADDINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class AddInstruction : public Instruction
{
    public:
        using Instruction::Instruction;
        virtual ~AddInstruction();

        void disassemble();
        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
