#include <iostream>
#include "registers.h"

using namespace std;

Registers::Registers ()
{
    m_registers[0] = 0;
    // Initialize program counter to zero
    m_PC = 0;

}

void Registers::setRegister(int regNum, int value){
    if(regNum != 0){
          m_registers[regNum] = value;
    }else{
        cout << "Error, $zero is fixed" << endl;
    }
}

int Registers::getRegister(int regNum){
    cout << "Return register value of " << m_registers[regNum];
    return m_registers[regNum];
}

void Registers::setPC(int value){
    m_PC = value;
}

int Registers::getPC(){
    return m_PC;
}

void Registers::print(){
    cout << "Register contents: " << endl;
    for(int i = 0; i < m_registers.size(); i++){
        cout << i << ": " << m_registers[i] << endl;
    }
    cout << "PC: " << m_PC << endl;

}
