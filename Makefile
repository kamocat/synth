fname = table
all: plot

build: $(fname).c* $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp table.cpp filter.c fm.c audio.cpp tone.c -o $(fname).out

run: build
	./$(fname).out

plot: run
	audacity sample.wav &> ./audacity.log &

play: run
	mplayer -really-quiet sample.wav
