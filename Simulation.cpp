#include "Simulation.h"

Simulation::Simulation(int rows, int cols, int max_gens, std::string& initial) : 
    _max_gens(max_gens), 
    _generation(0),
    _evolution(true),
    _stuck(false),
    _initial(initial),
    _previous(Board(rows, cols)),
    _current(Board(rows, cols)),
    _next(Board(rows, cols)) { 
        _current.populate(_initial);
    }

Simulation::~Simulation() { }

bool Simulation::isOver() {
    return _generation ==  _max_gens;
}

bool Simulation::isStuck() {
    return _stuck;
}

int Simulation::generation() {
    return _generation;
}

Board& Simulation::get_board() { 
    return _current; 
}

Board& Simulation::next() {
    int dead = 0, live = 1;
    for (int i = 0; i < _current.get_rows(); ++i) {
        for (int j = 0; j < _current.get_cols(); ++j) {
            int cell = _current.get(i, j);
            int npeers = peers(i, j);
            if (cell == dead) {
                if (npeers == 3) _next.set(i, j, live);
            } else {
                _next.set(i, j, ((npeers == 2 || npeers == 3) ? live : dead));
            }
        }
    }

    if (_evolution) {
        _evolution = false;
        _previous = Board(_current);
    } else {
        _evolution = true;
    }
    _current = Board(_next);

    if (_previous == _next) {
        _stuck = true;
        return _current;
    } 
    _next = Board(_current.get_rows(), _current.get_cols());
    if (!isStuck()) {
        _generation++;
    }
    return _current;
}

int Simulation::peers(int x, int y) {
    int n = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((x > 0 && x < _current.get_rows()-1) && (y > 0 && y < _current.get_rows()-1)) {
                n += _current.get(x + i, y + j);
            } else { // borders
                if ((x + i) > -1 && (x + i) < _current.get_rows()) {
                    if ((y + j) > -1 && (y + j) < _current.get_rows()) {
                        n += _current.get(x + i, y + j);
                    }
                }
            }
        }
    }
    return n - _current.get(x, y);
}


