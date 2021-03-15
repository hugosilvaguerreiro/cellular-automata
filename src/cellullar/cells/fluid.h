#ifndef FLUID_
#define FLUID_

#include <algorithm>
#include <iostream>
#include "cell.h"
#include "empty_cell.h"

class Fluid : public Cell {


    public:
        float density;
        float velocity_x = 0.0;
        float velocity_y = 0.0;
        float spread_rate = 0.25;
        Fluid(int x, int y) : Cell(x,y) {
            density = 1;
        }

        ~Fluid()  {}

        Fluid(const Fluid& other) : Fluid(other.posx, other.posy) { density = other.density;} //move constructor
        virtual Fluid& operator=(const Fluid& other) { //copy assignment
            if (this == &other) return *this;

            posx = other.posx; 
            posy = other.posy; 
            visited = other.visited;
            deleteMe = other.deleteMe;
            density = other.density;
            return *this;
        }



        float exchangeDensity(float quantity) {
            //returns the ammount that was not possible to accept
            float result = this->density + quantity;
            if(result > 1) {
                this->density = 1;
                return result - 1;
            } else {
                this->density = result;
                return 0;
            }   
        }

        float getDensityExchangeAmmount() {
            if(this->density - spread_rate < 0) {
                return this->density;
            } else {
                return spread_rate;
            }
        }
        void processDensity(EmptyCell* otherCell) {
                if(!otherCell->hasContents() && density > 0.5) {
                    Fluid* f = new Fluid(otherCell->posx, otherCell->posy);
                    f->visited = true;
                    f->density = 0.0;
                    otherCell->setContent(f);
                }

                if(otherCell->hasContents() && otherCell->getContent()->getType() == WATER) {
                    Fluid* f = (Fluid*) otherCell->getContent();
                    float ammountToExchange = getDensityExchangeAmmount();
                    float rest = f->exchangeDensity(ammountToExchange);
                
                    this->density += -ammountToExchange + rest;
                    std::cout << "this: " << this << " | " << "other: " 
                              << f << " | " << this->density << " " << ammountToExchange << " " << rest << " " << f->density << "\n";
                }
        }

        void simulate(Neighbors n) override {
            Cell* new_cell = this;

            float spread_available = spread_rate;

            if(n.down_left->getType() == EMPTY_CELL || 
               n.down_left->getType() == EMPTY_CELL ||
               n.down_right->getType() == EMPTY_CELL) {
                if(n.down->getType() == EMPTY_CELL) {
                    processDensity((EmptyCell *)n.down);
                }
                if(n.down_left->getType() == EMPTY_CELL && n.left->getType() != WALL_CELL) {
                    processDensity((EmptyCell *)n.down_left);
                }
                if(n.down_right->getType() == EMPTY_CELL && n.right->getType() != WALL_CELL) {
                    processDensity((EmptyCell *)n.down_right);
                }
            } else {
                if (n.right->getType() == EMPTY_CELL) {
                    processDensity((EmptyCell *)n.right);
                }
                if(n.left->getType() == EMPTY_CELL) {
                    processDensity((EmptyCell *)n.left);
                }
            }


            if(this->density == 0) {deleteMe = true; }
            else {deleteMe = false;}

            /*if(n.down->getType() == EMPTY_CELL) {
                new_cell = n.down;
            } else if (n.down_left->getType() == EMPTY_CELL && n.left->getType() == EMPTY_CELL) {
                new_cell = n.down_left;
            } else if(n.down_right->getType() == EMPTY_CELL && n.right->getType() == EMPTY_CELL) {
                new_cell = n.down_right;
            }
            this->posx = new_cell->posx;
            this->posy = new_cell->posy;*/
        }

        CELL_TYPE getType()  override {
            return WATER;
            
        }
};


#endif