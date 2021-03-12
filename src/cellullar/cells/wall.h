#ifndef WALL_
#define WALL_

#include "cell.h"

class Wall : public Cell {
    public:
        Wall() : Cell() {}
        Wall(int posx, int posy) : Cell(posx, posy) {}

        void simulate(Neighbors n) override {
            // Do nothing
        }

        CELL_TYPE getType()  override {
            return WALL_CELL;
        }
};

#endif