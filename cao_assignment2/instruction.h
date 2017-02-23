#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include "registers.h"

using namespace std;

class Instruction
{
private:
    string m_operation;
    int m_rd;
    int m_rs;
    int m_rt;
public:
    Instruction();
    virtual void disassemble();
    virtual int execute(Registers*);

    void setOperation(string operation);
    void setRD(int value);
    void setRS(int value);
    void setRT(int value);

    string getOperation();
    int getRD();
    int getRS();
    int getRT();

};

#endif /* _INSTRUCTION_H_ */
