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
    cout << "Sub instruction executed" << endl;
    Registers->setRegister(8, getRD());
    Registers->setRegister(9, getRT());
    Registers->setRegister(10, getRS());
    Registers->setRegister(getRD(), getRT() - getRS());
    return Registers->getPC() + 1;
}
