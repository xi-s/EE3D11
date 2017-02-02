#ifndef COMPUTER_H_INCLUDED
#define COMPUTER_H_INCLUDED

class Computer{
    private:
	double m_clockRateGHz;
	// CPI per each instruction class
	double m_cpiArith;
	double m_cpiStore;
	double m_cpiLoad;
	double m_cpiBranch;
    public: 
	// Constructor prototype
	Computer(double clockRateGHz, double cpiArith, double cpiStore, double cpiLoad, double cpiBranch);

	void printStats(); 
	double calculateGlobalCPI();
};


#endif // COMPUTER_H_INCLUDED
