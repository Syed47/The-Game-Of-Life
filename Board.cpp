#include "Board.h"

Board::Board(unsigned int rows, unsigned int cols) : 
    _rows(rows), 
    _cols(cols),
    _map(rows, std::vector<int>(cols)) { }


Board::Board(Board& other) : 
    _rows(other.get_rows()), 
    _cols(other.get_cols()), 
    _map(other._map) { }


Board::~Board() { }

void Board::populate(const char* initial) {
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

void Board::set(int row, int col, int value) {
    _map[row][col] = value;
}

void Board::show() {
    std::cout << "-----------------" << std::endl;
    for (std::vector<std::vector<int>>::iterator i = _map.begin(); i < _map.end(); i++) {
        for (std::vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
            std::cout << " " << *j;
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

int Board::get(int i, int j) { return _map[i][j]; }
int Board::get_rows() { return _rows; }
int Board::get_cols() { return _cols; }