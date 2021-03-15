#ifndef SIMULATOR
#define SIMULATOR

#include "cells/cell.h"
#include "cells/empty_cell.h"
#include "cells/world.h"
#include "cells/sand.h"
#include "cells/fluid.h"

class Simulator {
    public:
        World world;
        

        Simulator(int world_size_x, int world_size_y) : world(world_size_x, world_size_y) {}
        
        int T = 0;
        void createSand() {
            if(T < 10000) {
                for(int i = 0; i < 10; i++) {
                    int x = rand() % 80 + 1; 
                    int y = rand() % 50 + 1; 
                    if (T % 2 == 0) {
                        Cell* c = world.getCell(x, y);
                        if(c->getType() != WALL_CELL && c->getType() != SAND) {
                            Sand* s = new Sand(x,y);
                            delete world.getCell(x, y);
                            world.placeCell(s, x, y);

                        } else {T--;}
                        
                    }
                    T++;
                }
            }
        }

        bool alreadyCreated = false;
        void createWater() {
            if(!alreadyCreated) {
                for(int i = 0; i < 20; i++) {
                    ((EmptyCell*) world.getCell(30+i, 20))->setContent(new Fluid(170,20));
                    ((EmptyCell*) world.getCell(30+i, 21))->setContent(new Fluid(170,20));
                    ((EmptyCell*) world.getCell(30+i, 22))->setContent(new Fluid(170,20));
                    ((EmptyCell*) world.getCell(30+i, 23))->setContent(new Fluid(170,20));
                    ((EmptyCell*) world.getCell(30+i, 24))->setContent(new Fluid(170,20));
                }
                alreadyCreated = true;
            }
        }

        
        void doSimulationStep() {
            //createSand();
            createWater();


            /*for(Cell* c : world.importantCells) {
                Neighbors n = world.getNeighbors(c->posx, c->posy);
                if(!c->visited) {
                    int i = c->posx; int j = c->posy;
                    c->simulate(n);
                        
                    //Swap the two cells
                    Cell* old_cell = world.getCell(c->posx, c->posy);
                    old_cell->posx = i; old_cell->posy = j;
                    world.placeCell(old_cell, i, j);
                    world.placeCell(c, c->posx, c->posy);

                    c->visited = true;
                }
            }*/
            for(int i = 1; i < world.size_x-1; i ++) {
                for(int j = 1; j < world.size_y-1; j++) {
                    Cell* c = world.getCell(i, j);
                    Neighbors n = world.getNeighbors(i, j);

                    if(!c->visited) {
                        c->simulate(n);
                        
                        //Swap the two cells
                        Cell* old_cell = world.getCell(c->posx, c->posy);
                        old_cell->posx = i; old_cell->posy = j;
                        world.placeCell(old_cell, i, j);
                        world.placeCell(c, c->posx, c->posy);

                        c->visited = true;
                    }
                }
            }
        }

        void stop() {
            
        }
};

#endif