#include "Board.h"

Board::Board(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols) {
    _map = (int**) malloc(sizeof(int*) * _rows);
    for (int i = 0; i < _rows; ++i) {
        _map[i] = (int*) malloc(sizeof(int) * _cols);
    }
}

Board::Board(Board& other) {
    _map = (int**) malloc(sizeof(int*) * other.get_rows());
    for (int i = 0; i < other.get_rows(); ++i) {
        _map[i] = (int*) malloc(sizeof(int) * other.get_cols());
    }
}

Board::~Board() {
    for (int i = 0; i < _rows; ++i) {
        free(_map[i]);
    }
    free(_map);
}

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
    printf("-----------------\n");
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            printf("%d ", _map[i][j]);
        }
        printf("\n");
    }
    printf("-----------------\n");
}

int Board::get(int i, int j) { return _map[i][j]; }
int Board::get_rows() { return _rows; }
int Board::get_cols() { return _cols; }