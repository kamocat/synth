pitch = 440*2*pi;
fs = 44100;
seconds = 4;
n = fs*seconds;
wf = seconds*pitch;
rate = 2.9;
level = 5;

w = linspace(0,wf,n);
x = logspace(log10(level),-1,n) .* sin(linspace(0,wf*rate,n));
y = sin(w + x);

audiowrite("synth.wav", y, fs, 'BitsPerSample',8);