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
	Program(int numArith, int numStore, int numLoad, int numBranch, int numTotal);

	void printStats();
	double calculateGlobalCPI();
};

#endif
