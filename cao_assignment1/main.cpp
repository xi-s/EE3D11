#include <iostream>

#include "computer.h"
#include "program.h"

#define COUNT 3

using namespace std;

void print(Computer* computers, Program* programs){
    for(int i = 0; i < COUNT; i++){
        cout << "Computer: " << i << endl;
         for(int i = 0; i < COUNT; i++){
            cout << "Program " << i << ": " << endl;
            computers[i].calculateExecutionTime(programs[i]);
            computers[i].calculateMIPS(programs[i]);
        }
    }
}

int main(){
    Program programs[COUNT];
    programs[0] = Program(2000, 100, 100, 50);
    programs[1] = Program(2000, 0.1f, 0.4f,  0.25f);
    programs[2] = Program(500, 100, 2000, 200);

    Computer computers[COUNT];
    computers[0] = Computer(1.0, 2.0, 2.0, 3.0, 4.0);
    computers[1] = Computer(1.2, 2.0, 3.0, 4.0, 3.0);
    computers[2] = Computer(2.0, 2.0, 2.0, 4.0, 6.0);

    print(computers, programs);
    return 0;
}
