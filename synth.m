f = [0.5 1.5 1 2 3 4 5 6 7 8 9];
pitch = 440*2*pi;
fs = 44100;
seconds = 3;

w = linspace(0,seconds*pitch,fs*seconds);
w = f' * w;
w = sin(w);

a = [.1 .2 .3 .2 .1 .05 .02 .01 .01 .01 .01];
w = a * w;

player = audioplayer(w, fs);
play(player);
