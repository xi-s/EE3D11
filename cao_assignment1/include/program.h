#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

class Program{
    private:
        int m_numArith;
        int m_numStore;
        int m_numLoad;
        int m_numBranch;
        int m_numTotal;
    public:
        Program(int, int, int, int);
        // Overloaded constructor that accepts fractions
        Program(int, double, double, double);

        void printStats();
        double calculateGlobalCPI();

        int getArith(){ return m_numArith;};
        int getStore(){ return m_numStore;};
        int getLoad() { return m_numLoad;};
        int getTotal(){ return m_numBranch;};
};

#endif
