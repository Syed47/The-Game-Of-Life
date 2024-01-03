#include <cstdio>
#include <cstdlib>

using namespace std;

class Board {
    int _rows, _cols;
    int** _map;

public:
    Board(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols) {
        _map = (int**) malloc(sizeof(int*) * _rows);
        for (int i = 0; i < _rows; ++i) {
            _map[i] = (int*) malloc(sizeof(int) * _cols);
        }
    }

    Board(Board& other) {
        _map = (int**) malloc(sizeof(int*) * other.get_rows());
        for (int i = 0; i < other.get_rows(); ++i) {
            _map[i] = (int*) malloc(sizeof(int) * other.get_cols());
        }
    }

    void populate(const char* initial) {
        int ptr = 0, row = 0, col = 0;
        char c;
        while ((c = initial[ptr++]) != '\0') {
            if (c == '0') {
                _map[row][col++] = 0;
            } else if (c == '1') {
                _map[row][col++] = 1;
            } else if (c == '\n') {
                row++; col = 0;
            }
        }
    }

    void set(int row, int col, int value) {
        _map[row][col] = value;
    }

    void show() {
        printf("-----------------\n");
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                printf("%d", _map[i][j]);
            }
            printf("\n");
        }
        printf("-----------------\n");
    }

    int get(int i, int j) { return _map[i][j]; }
    int get_rows() { return _rows; }
    int get_cols() { return _cols; }
};


class Simulation {
    int _max_gens;
    const char* _initial;
    Board *_current, *_next;

public:
    Simulation(int rows, int cols, int max_gens, const char* initial) : 
        _max_gens(max_gens), 
        _initial(initial),
        _current(new Board(rows, cols)),
        _next(new Board(rows, cols)) { }

    void run() {
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
            printf("Generation: %d\n", _max_gens - gen);
            _current->show();
        }
    }

    int peers(int x, int y) {
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

    Board& get_board() { return *_current; }
};


int main()
{
    const char* initial = "11100\n01110\n00100\n10011\n10001\0";

    Simulation sim(5, 5, 10, initial);
    sim.run();
   
    return EXIT_SUCCESS;
}
