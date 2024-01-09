#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "Board.h"

class Simulation {
    int _max_gens;
    const char* _initial;
    Board _current, _next;

public:
    Simulation(int rows, int cols, int max_gens, const char* initial);
    ~Simulation();

    void run();
    int peers(int x, int y);
    Board& get_board();
};

#endif