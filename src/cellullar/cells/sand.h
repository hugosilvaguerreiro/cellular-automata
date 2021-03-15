#ifndef SAND_
#define SAND_

#include "cell.h"

class Sand : public Cell {
    public:
        Sand(int x, int y) : Cell(x,y) {}

        ~Sand()  {}


        void simulate(Neighbors n) override {
            Cell* new_cell = this;
            if(n.down->getType() == EMPTY_CELL) {
                new_cell = n.down;
            } else if (n.down_left->getType() == EMPTY_CELL && n.left->getType() == EMPTY_CELL) {
                new_cell = n.down_left;
            } else if(n.down_right->getType() == EMPTY_CELL && n.right->getType() == EMPTY_CELL) {
                new_cell = n.down_right;
            }
            this->posx = new_cell->posx;
            this->posy = new_cell->posy;
        }

        CELL_TYPE getType()  override {
            return SAND;
        }
};


#endif