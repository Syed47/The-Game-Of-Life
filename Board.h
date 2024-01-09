#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Board {
    int _rows, _cols;
    std::vector<std::vector<int>> _map;

public:
    Board(unsigned int rows, unsigned int cols);
    Board(Board& other);
    ~Board();

    void populate(const char* initial);
    void set(int row, int col, int value);
    void show();
    int get(int i, int j); 
    int get_rows();
    int get_cols();
};

#endif