#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include "Board.h"

class Simulation {
    int _generation;
    int _max_gens;
    bool _evolution, _stuck;
    std::string& _initial;
    Board _previous, _current, _next;

public:
    Simulation(int rows, int cols, int max_gens, std::string& initial);
    ~Simulation();

    int peers(int x, int y);
    bool isOver();
    bool isStuck();
    int generation();
    Board& next();
    Board& get_board();
};

#endif