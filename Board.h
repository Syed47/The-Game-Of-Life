#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

class Board {
    int _rows, _cols;
    std::vector<std::vector<int>> _map;

public:
    Board(unsigned int rows, unsigned int cols);
    Board(Board& other);
    ~Board();

    void populate(std::string& initial);
    void set(int row, int col, int value);
    void show();
    bool operator==(const Board& other);
    int get(int i, int j) const; 
    int get_rows();
    int get_cols();
};

#endif