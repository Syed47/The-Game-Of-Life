#include "Simulation.h"

int main()
{
    const char* initial = "11100\n01110\n00100\n10011\n10001\0";

    Simulation sim(5, 5, 10, initial);
    sim.run();
   
    return EXIT_SUCCESS;
}
