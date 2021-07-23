all: build run play

build: synth.c synth_tb.cpp
	g++ -g -ggdb synth_tb.cpp synth.c -o synth.out

run: synth.out
	./synth.out

plot: example.wav
	audacity example.wav &

play: example.wav
	mplayer -really-quiet example.wav
