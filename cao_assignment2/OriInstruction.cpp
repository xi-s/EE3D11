#include "oriinstruction.h"

OriInstruction::~OriInstruction(){
}

void OriInstruction::disassemble(){
        cout << "ori" << " $" << getRD() << ", $" << getRS() <<", " << getRT() << endl;
}

int OriInstruction::execute(Registers* Registers){
    disassemble();
    // Ori content of rs with immediate value of rt and store in rd
    Registers->setRegister(getRD(), Registers->getRegister(getRS()) | getRT());
    return Registers->getPC() + 1;
}
