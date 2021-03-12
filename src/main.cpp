#include "cellullar/cells/cell.h"
#include "cellullar/simulator.h"
#include "renderer.h"


class App : public Application {
    public:
        Simulator s;
        int renderScale;
        int size;

        App(Renderer& r, int size, int scale) : Application(r), s(size, size), renderScale(scale), size(size) {}

        void render_cells() {

            for(int i=0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    Cell* c = this->s.world.getCell(i, j);
                    RGBA color;
                    switch (c->getType()) {
                        case WALL_CELL:
                            color = {100,100,50, 255};
                        break;
                        case EMPTY_CELL:
                            color = {0,0,0,255};
                        break;
                        case SAND:
                            color = {200,200,200,255};  
                        break;
                    }
                        
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

        }
};

int main() {

    Renderer r(WINDOW_SIZE{1000,1000});
    App s = App(r, 200, 1000/200);
    r.start(s);
        
}