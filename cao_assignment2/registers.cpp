#include <iostream>
#include <iomanip>
#include "registers.h"

using namespace std;

Registers::Registers ()
{
    m_PC = 0;
}

void Registers::setRegister(int regNum, int value){
    // Make $zero read only
    if(regNum != 0){
          m_registers[regNum] = value;
    }else{
        cout << "Error, $zero is fixed" << endl;
    }
}

int Registers::getRegister(int regNum){
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
        cout << "$" << i << ":\t" << m_registers[i] << endl;
    }
    cout << "PC:\t" << m_PC << endl;

}
