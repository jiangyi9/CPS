% Sample t at f_s=1000Hz for 0.3sec
f_s = 1000;
t = 0:1/f_s:0.3; % values from 0 to 10 in steps of 0.001
% Generation of sample sin wave
phase_sin = 0;
amplitude_sin = 1;
f_sin = 20; % 20Hz base signal
omega_sin = 2*pi*f_sin;
signal_sin = amplitude_sin * sin(omega_sin*t + phase_sin);

% Generation of noise signal
phase_noise = 0;
amplitude_noise = 1;
f_noise = 400; % 400Hz noise signal
omega_noise = 2*pi*f_noise;
signal_noise = amplitude_noise*sin(omega_noise*t + phase_noise);
% Combine sin signal with noise
signal_combined = signal_sin + signal_noise;

% export the combined signal with noise
dlmwrite("signal_combined.csv",signal_combined.','precision','%.6f');

% plot the combined signal with noise
subplot(2,1,1);
plot(t, signal_combined);
xlabel('Time')
ylabel('Amplitude')
title('Original Signal (with noise)');

% Butterworth filter
Wp = 40/500;
Ws = 200/500;
[n,Wn] = buttord(Wp,Ws,3,40);
[b,a] = butter(n,Wn);
signal_new = filter(b,a,signal_combined);

% plot the new signal processed by the Butterworth filter
subplot(2,1,2);
plot (t, signal_new ) ;
xlabel('Time');
ylabel('Amplitude');
title('Signal passed the Butterworth filter');

% % plot the Bode plot
% freqz(b,a,512,1000);
% title(sprintf('n=%d Butterworth Lowpass Filter',n));

