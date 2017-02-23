#ifndef BRNEINSTRUCTION_H
#define BRNEINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class BrneInstruction : public Instruction
{
    public:
        BrneInstruction(int, int, int);
        virtual int execute(Registers*);
        virtual ~BrneInstruction();

    protected:

    private:
};

#endif // ADDINSTRUCTION_H
