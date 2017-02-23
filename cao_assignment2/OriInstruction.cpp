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
    cout << "Ori instruction executed" << endl;
    Registers->setRegister(8, getRD());
    Registers->setRegister(9, getRT());
    Registers->setRegister(10, getRS());
    Registers->setRegister(getRD(), getRS() | getRT());
    return Registers->getPC() + 1;
}
