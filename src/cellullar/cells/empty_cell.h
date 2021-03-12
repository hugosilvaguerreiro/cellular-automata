#ifndef EMPTY_CELL_
#define EMPTY_CELL_

#include "cell.h"

class EmptyCell : public Cell {
    public:
        EmptyCell(int x, int y) : Cell(x,y) {}

        void simulate(Neighbors n) override {
            //Do Nothing;
        };

        CELL_TYPE getType() override {
            return EMPTY_CELL;
        }
};

#endif