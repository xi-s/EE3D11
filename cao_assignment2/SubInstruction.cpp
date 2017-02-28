#include "subinstruction.h"

SubInstruction::~SubInstruction(){
}

void SubInstruction::disassemble(){
        cout << "sub" << " $" << getRD() << ", $" << getRS() <<", $" << getRT() << endl;
}

int SubInstruction::execute(Registers* Registers){
    disassemble();
    // subtract rt from rs and store result in rd
    Registers->setRegister(getRD(), Registers->getRegister(getRS()) - Registers->getRegister(getRT()));
    return Registers->getPC() + 1;
}
