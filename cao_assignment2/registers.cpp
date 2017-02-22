#include <iostream>
#include "registers.h"

using namespace std;

Registers::Registers ()
{
    registers[0] = 0;
    // Initialize program counter to zero
    PC = 0;

}

void Registers::setRegister(int regNum, int value){
    if(regNum != 0){
          registers[regNum] = value;
    }else{
        cout << "Error, $zero is fixed" << endl;
    }
}

int Registers::getRegister(int regNum){
    cout << "Return register value of " << registers[regNum];
    return registers[regNum];
}

void Registers::setPC(int value){
    PC = value;
}

int Registers::getPC(){
    return PC;
}

void Registers::print(){
    cout << "Register contents: " << endl;
    for(int i = 0; i < registers.size(); i++){
        cout << i << ": " << registers[i] << endl;
    }
    cout << "PC: " << PC << endl;

}
