#include "Simulation.h"

Simulation::Simulation(int rows, int cols, int max_gens, const char* initial) : 
    _max_gens(max_gens), 
    _initial(initial),
    _current(new Board(rows, cols)),
    _next(new Board(rows, cols)) { }

Simulation::~Simulation() {
    delete _current;
}

void Simulation::run() {
    int dead = 0, live = 1, gen = _max_gens;
    _current->populate(_initial);
    printf("Population\n");
    _current->show();
    while (gen-- != 0) {
        _next = new Board(_current->get_rows(), _current->get_cols());
        for (int i = 0; i < _current->get_rows(); ++i) {
            for (int j = 0; j < _current->get_cols(); ++j) {
                int cell = _current->get(i, j);
                int npeers = peers(i, j);
                if (cell == dead) {
                    if (npeers == 3) {
                        _next->set(i, j, live);
                    }
                } else {
                    _next->set(i, j, ((npeers == 2 || npeers == 3) ? live : dead));
                }
            }
        }
        _current = _next;
        // delete _next;
        printf("Generation: %d\n", _max_gens - gen);
        _current->show();
    }
}

int Simulation::peers(int x, int y) {
    int n = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((x > 0 && x < _current->get_rows()-1) && (y > 0 && y < _current->get_rows()-1)) {
                n += _current->get(x + i, y + j);
            } else { // borders
                if ((x + i) > -1 && (x + i) < _current->get_rows()) {
                    if ((y + j) > -1 && (y + j) < _current->get_rows()) {
                        n += _current->get(x + i, y + j);
                    }
                }
            }
        }
    }
    return n - _current->get(x, y);
}

Board& Simulation::get_board() { return *_current; }

