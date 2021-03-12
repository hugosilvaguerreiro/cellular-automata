#ifndef CELL
#define CELL

enum CELL_TYPE {
    EMPTY_CELL,
    WALL_CELL,
    SAND,
};


class Cell;
struct Neighbors {
    Cell* left;
    Cell* right;

    Cell* up;
    Cell* up_left;
    Cell* up_right;
    
    Cell* down;
    Cell* down_left;
    Cell* down_right;
};

class Cell {
    public:
        int posx; int posy;
        bool visited;

        Cell() : Cell(0,0) {}
        Cell(int posx, int posy) : posx(posx), posy(posy), visited(false){}

        virtual void simulate(Neighbors n) = 0;
        virtual CELL_TYPE getType() = 0;
    
};

#endif