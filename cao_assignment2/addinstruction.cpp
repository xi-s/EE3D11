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
    disassemble();
    // Add rs to rt and store in rd
    Registers->setRegister(getRD(), Registers->getRegister(getRS()) + Registers->getRegister(getRT()));
    return Registers->getPC() + 1;
}
