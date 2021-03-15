PROGRAM_NAME = cellular

GCC	= g++
BIN	= bin/$(PROGRAM_NAME)

SRC = src

SOURCES = src/renderer.cpp src/main.cpp
INCS	= -lsfml-graphics -lsfml-window -lsfml-system
LIBS	= 

LINKOBJ	= $(SOURCES:.cpp=.o)

all: clean $(BIN)

$(BIN): $(LINKOBJ)
	$(GCC) -g $(LINKOBJ) $(INCS) $(LIBS) -o $(BIN) -std=c++0x

.cpp.o:
	$(GCC) -g -c $< -o $@ $(INCS) -std=c++0x

clean:
	rm -f $(LINKOBJ)
	rm -f $(BIN)

run: clean $(BIN)
	$(BIN)

valgrind:
	valgrind --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         $(BIN)

