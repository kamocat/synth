all: build run plot

build: synth.c
	gcc synth.c -o synth.exec

run: synth.exec
	./synth.exec > dat.csv

plot: dat.csv
	gnuplot plot_settings
