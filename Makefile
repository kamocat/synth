fname = table
all: play

build: $(fname).c* $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp table.cpp fm.c audio.cpp tone.c -o $(fname).out

run: build
	./$(fname).out

plot: run
	audacity sample.wav &> ./audacity.log &

play: run
	mplayer -really-quiet sample.wav
