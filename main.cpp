#include <string>
#include "Simulation.h"

#ifndef _PARAMS_
    #define ROWS 5
    #define COLS 5
    #define GENERATIONS 10
#endif

std::string& random_population(int r, int c) {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::string* population = new std::string();
    for (uint32_t i = 0; i < r; i++) {
        for (uint32_t j = 0; j < c; j++)
            *population += rand() % 2 == 0 ? "0 " : "1 ";
        *population += "\n";
    }
    return *population;
}

int main()
{
    std::string initial = "11100\n01110\n00100\n10011\n10001\0";
    // std::string initial = random_population(ROWS, COLS);
    Simulation sim(ROWS, COLS, GENERATIONS, initial);
    sim.run();
   
    return EXIT_SUCCESS;
}
