#include "simulator.h"
#include "program.h"
#include "registers.h"

#include "addinstruction.h"
#include "subinstruction.h"
#include "oriinstruction.h"
#include "brneinstruction.h"

void loadProgram (Program *program)
{
    /*
        Probably equivalent to the following pseudocode:
        $1 contains 12
        $2 contains 3
        $3 contains 1
        $4 contains 12 (initially)

        do{
            $4 += $1;
            $2 -= $3;
        }
        while($2 != 0);

        $2 goes to zero after decrementing three times.
        Because the while condition is met before executing the next addition,
        The value 12 will be added to $4 only twice.

        This is akin to multiplication by repeated addition

    */
    program->appendInstruction (new OriInstruction (1, 0, 12));
	program->appendInstruction (new OriInstruction (2, 0, 4));
	program->appendInstruction (new OriInstruction (3, 0, 1));
	program->appendInstruction (new AddInstruction (4, 4, 1));
	program->appendInstruction (new SubInstruction (2, 2, 3));
	program->appendInstruction (new BrneInstruction (2, 0, -3));
	program->appendInstruction (new AddInstruction(0, 0, 10));
}

int main (void)
{
	Registers *registers	= new Registers ();
	Program	*program	= new Program ();

	loadProgram (program);

	Simulator theSimulator = Simulator (registers, program);

	theSimulator.ui ();

	return 0;
}
