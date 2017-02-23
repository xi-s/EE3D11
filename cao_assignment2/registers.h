#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <array>

class Registers
{
private:

   std::array<int, 32> m_registers{};
    int m_PC;
   /* // Specify MIPS registers:
    int $zero;

    // Assembler temporary
    int $at;

    // Return vslue
    int $v0;
    int $v1;

    // Arguments
    int $a0;
    int $a1;
    int $a2;
    int $a3;

    // Temps
    int $t0;
    int $t1;
    int $t2;
    int $t3;
    int $t4;
    int $t5;
    int $t6;
    int $t7;

    // Saved registers
    int $s0;
    int $s1;
    int $s2;
    int $s3;
    int $s4;
    int $s5;
    int $s6;
    int $s7;

    // Temps
    int $t8;
    int $t9;

    // Reserved for OS kernel
    int $k0;
    int $k1;

    int $gp; // global pointer
    int $sp; // stack pointer
    int $fp; // frame pointer
    int $ra; // return address
    */
public:
    Registers();
    void setRegister(int regNum, int value);
    int getRegister(int regNum);
    void setPC(int value);
    int getPC();
    void print();
};

#endif	/* _REGISTERS_H_ */
