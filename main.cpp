#include "Simulation.h"

#ifndef _PARAMS_
    #define ROWS 5
    #define COLS 5
    #define GENERATIONS 10
#endif

int main()
{
    const char* initial = "11100\n01110\n00100\n10011\n10001\0";

    Simulation sim(ROWS, COLS, GENERATIONS, initial);
    sim.run();
   
    return EXIT_SUCCESS;
}
