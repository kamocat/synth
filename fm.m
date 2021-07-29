pitch = 441*2*pi;
fs = 44100;
seconds = 4;
n = fs*seconds;
wf = seconds*pitch;
rate = 3.30;
level = 5;

w = linspace(0,wf,n);
x = logspace(log10(level),-1,n) .* sin(linspace(0,wf*rate,n));
y = sin(w + x);
y = y .* logspace(0,-2,n);

audiowrite("synth.wav", y, fs, 'BitsPerSample',8);
unix("mplayer synth.wav");