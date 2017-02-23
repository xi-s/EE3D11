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
    disassemble();
    if(Registers->getRegister(getRD()) != Registers->getRegister(getRS())){
        return Registers->getPC() + 1 + getRT();
    }else{
         return Registers->getPC() + 1;
    }
}
