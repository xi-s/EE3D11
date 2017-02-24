#include "brneinstruction.h"

BrneInstruction::BrneInstruction(int rd, int rs, int rt)
{
    setOperation("brne");
    setRD(rd);
    setRS(rs);
    setRT(rt);
}

BrneInstruction::~BrneInstruction(){
}

int BrneInstruction::execute(Registers* Registers){
    disassemble();
    // If rd == rs, we increment by the immediate value,
    // else we just increment the program counter with 1
    if(Registers->getRegister(getRD()) != Registers->getRegister(getRS())){
        return Registers->getPC() + 1 + getRT();
    }else{
         return Registers->getPC() + 1;
    }
}
