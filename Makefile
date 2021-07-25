fname = filter
all: build run play
#all: build run plot

build: $(fname).c $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp $(fname).c -o $(fname).out

run: $(fname).out
	./$(fname).out

plot: build run
	audacity $(fname).wav &

play: $(fname).wav
	mplayer -really-quiet $(fname).wav
