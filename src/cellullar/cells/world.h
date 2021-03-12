#ifndef WORLD
#define WORLD

#include <vector>
#include <iostream>

#include "cell.h"
#include "wall.h"
#include "empty_cell.h"
#include "sand.h"


inline bool drawTime(int i, int j) {
    //if ( 10 < i && i < 50 && j == 50) return true;
    if ( i == 10 && j >= 50 && j < 80) return true;
    if ( i == 50 && 50 <= j && j < 80) return true;


    /*if ( 10 < i && i < 50 && j == 100) return true;
    if ( i == 10 && j >= 70 && j < 100) return true;
    if ( i == 50 && 70 <= j && j < 100) return true;*/

    //if ( 10 < i && i < 50 && j == 100) return true;
    if ( i == 10 && j >= 70 && j < 100) return true;
    if ( i == 50 && 70 <= j && j < 100) return true;

    if (i == j-90 && 100 <= j && j < 118 ) return true;
    if (i == 200-j-50 && 100 <= j && j < 118 ) return true;


    if (i == 200-j-55 && 118 <= j && j < 136 ) return true;
    if (i == j-85 && 118 <= j && j < 136 ) return true;

    if ( i == 10 && j >= 136 && j < 186) return true;
    if ( i == 50 && 136 <= j && j < 186) return true;

    if ( 10 < i && i < 50 && j == 186) return true;

    return false;
}

class World {
    std::vector<std::vector<Cell*>> world;

    public:
        int size_x; int size_y;

        World(int size_x, int size_y) : size_x(size_x), size_y(size_y) {
            for(int i = 0; i < size_x; i++) {
                std::vector<Cell*> v;
                for(int j = 0; j < size_y; j++) {
                    // Place the surrounding walls
                    if(i == 0 || i == size_x-1 || j == 0 || j == size_y - 1 || drawTime(i, j)) {//(30 < i && i < 60 && 30< j && j < 35) || (50 < i && i < 80 && 50 < j && j < 60)) { 
                        Wall* w = new Wall(i,j);
                        v.push_back(w);
                    } else { // Fill the rest with empty cells
                        EmptyCell* e = new EmptyCell(i,j);
                        v.push_back(e);
                    }
                }
                this->world.push_back(v);
            }
        }

        Cell* getCell(int x, int y) {
            return world[x][y];
        }

        void placeCell(Cell* cell, int x, int y) {
            if(x > size_x || y > size_y) {
                std::cerr << "ERROR: " << x << " " << y << "\n";
                exit(0);
            }
            //std::cout << world.size() << " " << world.at(x).size() << " "  << x << " " << y << " " << cell << "\n";
            world.at(x).at(y) = cell;//[y] = cell;
        }

        Neighbors getNeighbors(int x, int y) { 
            // Failsafe to avoid querying the neighbors of the surrounding walls
            if(x <= 0 || x >= size_x || y <= 0 || y >= size_y) {
                std::cerr << "( " << x << ", " << y << ") It is not possible to get the Neighbors for the surrounding walls or outside the Surrounding walls\n";
                exit(0);
            }

            return Neighbors{
                this->getCell(x-1,y), //left
                this->getCell(x+1,y), //right
                this->getCell(x,y-1), //up
                this->getCell(x-1,y-1), //up left
                this->getCell(x-1,y+1), //up right 
                this->getCell(x,y+1), //down
                this->getCell(x-1,y+1), //down left
                this->getCell(x+1,y+1), //down right
            };
        }
};

#endif