f_s = 1000;
t = 0:1/f_s:0.3;

signal_combined = csvread("signal_combined.csv").';
subplot(2,1,1);
plot(t, signal_combined);
xlabel('Time (s)')
ylabel('Amplitude (dB)')
title('Original Signal (with noise)');

signal_new = csvread("signal_new.csv");
subplot(2,1,2);
plot (t, signal_new ) ;
xlabel('Time (s)');
ylabel('Amplitude (dB)');
title('Signal processed by the C language filter');