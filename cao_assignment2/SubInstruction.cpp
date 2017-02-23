#include "subinstruction.h"

SubInstruction::SubInstruction(int rd, int rs, int rt)
{
    setOperation("sub");
    setRD(rd);
    setRS(rs);
    setRT(rt);
}

SubInstruction::~SubInstruction()
{
    //dtor
}

int SubInstruction::execute(Registers* Registers){
    disassemble();
    // subtract rt from rs and store result in rd
    Registers->setRegister(getRD(), Registers->getRegister(getRS()) - Registers->getRegister(getRT()));
    return Registers->getPC() + 1;
}
