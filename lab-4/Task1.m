clc
clear

%the transfer fuction of the DC motor
J = 0.01;
b = 0.1;
Kt = 0.01;
L = 0.05;
R = 0.75;
Ke = 0.01;

%prove the open-loop system is stable by pzmap
s = tf('s');
P = 1/( (L*J/Kt)*s^2 + (L*b/Kt+R*J/Kt)*s + (Ke+R*b/Kt) );
figure(2)
subplot(2,1,1)
pzmap(P);
%find the step-response
subplot(2,1,2)
step(P);

% find rise time, overshoot, steady-state error
%Proportional control
t = 0:0.01:2;
Kp = 200;
C = pid(Kp);
T = feedback(C*P,1);
figure(3)
subplot(3,1,1)
step(T,t);
title('Proportional control')

%PD control
Kp = 30;
Kd = 10;
C = pid(Kp,0,Kd);
T = feedback(C*P,1);
subplot(3,1,2)
step(T,t);
title('PD control')

%PID control
Kp = 200;
Ki = 300;
Kd = 50;
C = pid(Kp,Ki,Kd)
T = feedback(C*P,1);
subplot(3,1,3)
step(T,t);
title('PID control')

