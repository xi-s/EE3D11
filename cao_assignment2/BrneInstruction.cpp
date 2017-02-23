#include "brneinstruction.h"

BrneInstruction::BrneInstruction(int rd, int rs, int rt)
{
    setOperation("brne");
    setRD(rd);
    setRS(rs);
    setRT(rt);
}

BrneInstruction::~BrneInstruction()
{
    //dtor
}

int BrneInstruction::execute(Registers* Registers){
    cout << "Brne instruction executed" << endl;
    Registers->setRegister(8, getRD());
    Registers->setRegister(9, getRT());
    Registers->setRegister(10, getRS());
    Registers->setRegister(getRD(), getRT() + getRS());
    return Registers->getPC() + 1;
}
