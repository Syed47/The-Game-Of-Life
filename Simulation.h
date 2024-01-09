#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include "Board.h"

class Simulation {
    int _max_gens;
    std::string& _initial;
    Board _current, _next;

public:
    Simulation(int rows, int cols, int max_gens, std::string& initial);
    ~Simulation();

    void run();
    int peers(int x, int y);
    Board& get_board();
};

#endif