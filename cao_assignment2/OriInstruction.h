#ifndef ORIINSTRUCTION_H
#define ORIINSTRUCTION_H

#include "instruction.h"
#include "registers.h"

class OriInstruction : public Instruction
{
    public:
        using Instruction::Instruction;
        virtual ~OriInstruction();

        void disassemble();
        int execute(Registers*);
};

#endif // ADDINSTRUCTION_H
