fname = fm
all: play

build: $(fname).c* $(fname)_tb.cpp
	g++ -g -ggdb $(fname)_tb.cpp fm.c table.cpp audio.cpp midi.cpp -o $(fname).out

run: build
	./$(fname).out

plot: run
	audacity sample.wav &> ./audacity.log &

play: run
	mplayer -really-quiet sample.wav
