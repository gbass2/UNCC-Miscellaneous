% Problem 2
[y, Fs] = audioread('problem2.wav');
x = y*3;

R = 1;
C = .0003183;
delta_t = 1/Fs;
stop = length(y) - 1;
t = [0:delta_t:delta_t*stop]; 
Vc = [0];

% Solving for Vc
for n = 1:1: stop
    Vc(n+1) = (delta_t/(R*C))*(x(n) - Vc(n)) + Vc(n);
end

% Cleaning up the audio
Y = x - Vc';

figure(1)
%Plot of the distorted audio
subplot(2,1,1)
plot(t,x)
title('Problem 2 : Input');
ylabel('Distorted Audio');
grid on;
axis([t(1), t(end), -3, 3])

% Plot after the filter has beeen applied
subplot(2,1,2)
plot(t,Y)
title('Output');
xlabel('Time (s)');
ylabel('Filtered Audio');
grid on;
axis([t(1), t(end), -1.2, 1.2])
