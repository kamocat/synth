pitch = 440*2*pi;
fs = 44100;
seconds = 3;
n = fs*seconds;
wf = seconds*pitch;
rate = 5;
level = 0.6;

w = linspace(0,wf,n);
x = linspace(0,1,n) .* sin(linspace(0,wf*rate,n));
y = sin(w + x);

audiowrite("synth.wav", y, fs, 'BitsPerSample',8);