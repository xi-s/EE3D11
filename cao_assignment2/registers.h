#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <array>

class Registers
{
    private:
       std::array<int, 32>  m_registers{};
       int                  m_PC;

    public:
        Registers();
        void    setRegister(int regNum, int value);
        int     getRegister(int regNum);
        void    setPC(int value);
        int     getPC();
        void    print();
};

#endif	/* _REGISTERS_H_ */
