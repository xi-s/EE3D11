#ifndef ADDINSTRUCTION_H
#define ADDINSTRUCTION_H

#include <instruction.h>


class AddInstruction : public Instruction
{
    public:
        AddInstruction();
        AddInstruction(int rd, int rs, int rt);
        virtual ~AddInstruction();

    protected:

    private:
};

#endif // ADDINSTRUCTION_H
