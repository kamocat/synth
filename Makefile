all: build run plot

build: synth.c
	g++ synth_tb.cpp synth.c -o synth.out

run: synth.out
	./synth.out

plot: example.wav
	audacity example.wav
