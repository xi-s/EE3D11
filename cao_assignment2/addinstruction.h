#ifndef ADDINSTRUCTION_H
#define ADDINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class AddInstruction : public Instruction
{
    public:
        AddInstruction(int, int, int);
        virtual int execute(Registers*);
        virtual ~AddInstruction();

    protected:

    private:
};

#endif // ADDINSTRUCTION_H
