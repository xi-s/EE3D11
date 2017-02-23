#include "instruction.h"

Instruction::Instruction(){

}

void Instruction::disassemble(){
   cout << getOperation() << " rd(" << getRD() << "), rs(" << getRS() <<"), rt(" << getRT() << ")" << endl;
}

int Instruction::execute(Registers*){
}

string Instruction::getOperation(){
    return m_operation;
};

void Instruction::setOperation(string operation){
    m_operation = operation;
}

void Instruction::setRD(int value){
    m_rd = value;
}

void Instruction::setRS(int value){
    m_rs = value;
}

void Instruction::setRT(int value){
    m_rt = value;
}

int Instruction::getRD(){
    return m_rd;
}

int Instruction::getRS(){
    return m_rs;
}

int Instruction::getRT(){
    return m_rt;
}
