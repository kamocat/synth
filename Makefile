fname = table
all: play

build: $(fname).c* $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp table.cpp fm.c tone.c -o $(fname).out

run: build
	./$(fname).out

plot: run
	audacity $(fname).wav &> ./audacity.log &

play: run
	mplayer -really-quiet $(fname).wav
