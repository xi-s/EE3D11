#include "addinstruction.h"

AddInstruction::~AddInstruction(){
}

void AddInstruction::disassemble(){
        cout << "add" << " $" << getRD() << ", $" << getRS() <<", $" << getRT() << endl;
}

int AddInstruction::execute(Registers* Registers){
    disassemble();
    // Add rs to rt and store in rd
    Registers->setRegister(getRD(), Registers->getRegister(getRS()) + Registers->getRegister(getRT()));
    return Registers->getPC() + 1;
}
