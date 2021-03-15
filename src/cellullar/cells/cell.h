#ifndef CELL
#define CELL

enum CELL_TYPE {
    EMPTY_CELL,
    WALL_CELL,
    SAND,
    WATER,
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
        bool deleteMe = false;

        Cell() : Cell(0,0) {}
        virtual ~Cell() {}


        Cell(const Cell& other) : Cell(other.posx, other.posy){ visited = other.visited;} //move constructor
        virtual Cell& operator=(const Cell& other) { //copy assignment
            if (this == &other) return *this;

            posx = other.posx; 
            posy = other.posy; 
            visited = other.visited;
            deleteMe = other.deleteMe;
            return *this;
        }

        Cell(int posx, int posy) : posx(posx), posy(posy), visited(false){}

        virtual void simulate(Neighbors n) = 0;
        virtual CELL_TYPE getType() = 0;
        virtual bool canBeRemoved() { return deleteMe;}
};

#endif