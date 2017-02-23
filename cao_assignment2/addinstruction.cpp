#include "addinstruction.h"

AddInstruction::AddInstruction(int rd, int rs, int rt)
{
    setOperation("add");
    setRD(rd);
    setRS(rs);
    setRT(rt);
}

AddInstruction::~AddInstruction()
{
    //dtor
}

int AddInstruction::execute(Registers* Registers){
    cout << "Add instruction executed" << endl;
    Registers->setRegister(8, getRD());
    Registers->setRegister(9, getRT());
    Registers->setRegister(10, getRS());
    Registers->setRegister(getRD(), getRT() + getRS());
    return Registers->getPC() + 1;
}
