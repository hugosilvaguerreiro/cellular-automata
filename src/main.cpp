#include "cellullar/cells/cell.h"
#include "cellullar/cells/fluid.h"
#include "cellullar/cells/sand.h"
#include "cellullar/simulator.h"
#include "renderer.h"
#include <SFML/Window/Mouse.hpp>
#include <cstdlib>
#include <iostream>


class App : public Application {

    class Handler : public MouseHandler {
        public:
            const int RADIUS = 5;
            const int NR_PARTICLES = 10;

            App* app;
            Handler(App* app) : app(app) {}
            
            bool inBounds(int x, int y) {
                return !(x <= 0 || x >= app->s.world.size_x || y <= 0 || y >= app->s.world.size_y);
            }

            void onLeftClick(int mousex, int mousey)  override {
                
                int x = mousex / app->renderScale;
                int y = mousey / app->renderScale;
                if(inBounds(x, y)) {
                    for(int i=0; i < NR_PARTICLES; i++) {

                        int new_x = x+RADIUS + (rand() % static_cast<int>(x+RADIUS - x + 1));
                        int new_y = y+RADIUS + (rand() % static_cast<int>(y+RADIUS - y + 1));

                        //min + (rand() % static_cast<int>(max - min + 1))
                        if(inBounds(new_x, new_y)) {
                            Cell* c2 = app->s.world.getCell(new_x, new_y);

                            if(c2->getType() == EMPTY_CELL) {
                                delete app->s.world.getCell(new_x, new_y);
                                Sand* c = new Sand(new_x, new_y);
                                c->visited = true;
                                app->s.world.placeCell(c, new_x, new_y);
                            }
                        }
                    }
                }            
            }
    };

    public:

        Simulator s;
        int renderScale;
        int size;
        Handler handler;

        App(Renderer& r, int size, int scale) : Application(r), s(size, size), renderScale(scale), size(size), handler(this) {
            std::cout << this << "\n";
            renderer->registerMouseHandler(handler);
        }

        ~App() {

        }

        RGBA getColor(Cell* c) {
            unsigned short s = 0;
            switch (c->getType()) {
                case WALL_CELL:
                    return {100,100,50, 255};
                break;
                case EMPTY_CELL:
                    if(((EmptyCell*)c)->hasContents()) {
                        return getColor(((EmptyCell*)c)->getContent());
                    }
                    return {0,0,0,255};
                break;
                case SAND:
                    return {200,200,200,255};  
                break;
                case WATER:
                    s = ((Fluid*)c)->density * 255;
                    return {255,255,255, s};  
                break;
                default:
                    return {0,0,0,255};
                break;
            }
        }

        void render_cells() {
            for(int i=0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    Cell* c = this->s.world.getCell(i, j);
                    RGBA color =  getColor(c);                       
                    this->renderer->renderSquare(i*renderScale, j*renderScale, renderScale , color);
                    c->visited = false;
                }
            }
        }

        void execute() {
            //called every frame
            s.doSimulationStep();
            render_cells();
            this->renderer->renderFrame();
        }

        void stop() {
            //called after the window as closed
            this->s.stop();

        }


};

int main() {

    Renderer r(WINDOW_SIZE{1000,1000});
    App s(r, 200, 1000/200);
    std::cout << &s << "\n";
    r.start(s);
        
}