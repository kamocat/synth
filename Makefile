fname = synth
all: build run play

build: $(fname).c $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp $(fname).c -o $(fname).out

run: $(fname).out
	./$(fname).out

plot: $(fname).wav
	audacity $(fname).wav &

play: example.wav
	mplayer -really-quiet $(fname).wav
