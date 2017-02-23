#ifndef ORIINSTRUCTION_H
#define ORIINSTRUCTION_H

#include <instruction.h>
#include "registers.h"

class OriInstruction : public Instruction
{
    public:
        OriInstruction(int, int, int);
        virtual int execute(Registers*);
        virtual ~OriInstruction();

    protected:

    private:
};

#endif // ADDINSTRUCTION_H
