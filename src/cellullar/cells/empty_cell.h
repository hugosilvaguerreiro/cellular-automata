#ifndef EMPTY_CELL_
#define EMPTY_CELL_

#include "cell.h"

class EmptyCell : public Cell {
    Cell* contents = nullptr;

    //Can be filled by other cells
    public:

        EmptyCell(int x, int y) : Cell(x,y) {}

        bool hasContents() {
            return contents != nullptr;
        }

        void deleteContent() {
            if(hasContents()) {
                delete contents;
                contents = nullptr;
            }
        }

        void setContent(Cell* content) {
            contents = content;
        }

        Cell* getContent() {
            return contents;
        }

        void simulate(Neighbors n) override {
            if(contents != nullptr)  {
                contents->simulate(n);
                
                if(contents->canBeRemoved()) {
                    delete contents;
                    contents = nullptr;
                }
            }
        };

        CELL_TYPE getType() override {                
            return EMPTY_CELL;
        }
};

#endif