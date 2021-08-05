fname = midi
all: plot

build: $(fname).c* $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp table.cpp audio.cpp midi.cpp -o $(fname).out

run: build
	./$(fname).out

plot: run
	audacity sample.wav &> ./audacity.log &

play: run
	mplayer -really-quiet sample.wav
