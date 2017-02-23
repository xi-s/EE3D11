#include "oriinstruction.h"

OriInstruction::OriInstruction(int rd, int rs, int rt)
{
    setOperation("ori");
    setRD(rd);
    setRS(rs);
    setRT(rt);
}

OriInstruction::~OriInstruction()
{
    //dtor
}

int OriInstruction::execute(Registers* Registers){
    disassemble();
    // Ori content of rs with immediate value of rt and store in rd
    Registers->setRegister(getRD(), Registers->getRegister(getRS()) | getRT());
    return Registers->getPC() + 1;
}
