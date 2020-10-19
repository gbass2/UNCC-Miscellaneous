% Problem 4 part F
clear all; clc; close all;

L = 0.01;
R = 3.38;
K = 0.029;
J = 2 * 10^(-4);
beta = 0.5 * 10^(-5);
delta_t = 6/2000000;
t = 0:delta_t:50; % Replace 10 with 50 in part e



ia = [0];
%Va(1:1:length(t)) = 10; % Used in part C and D
Theta = [0];
omega = [0];
Kadj = .1;              % Equal 1 in part e and .1 in part f
ThetaRef = pi/4;
Va(1) = Kadj*(ThetaRef - Theta(1));

for n = 1:1:length(t)-1
    ia(n+1) = (delta_t/L)*((-K * omega(n))-(R * ia(n))+ Va(n))+ ia(n);
    omega(n+1) = (delta_t/J)*(K * ia(n)- beta * omega(n))+ omega(n);
    Theta(n+1) = delta_t*omega(n) + Theta(n);
    Va(n+1) = Kadj*(ThetaRef - Theta(n));
end

% Part c
% figure(1);
% subplot(2,1,1);       
% plot(t,ia);
% title('Problem 4.C Current vs Time');
% xlabel('Time(s)');
% ylabel('Current(A)');
% subplot(2,1,2);
% plot(t,omega);
% title('Problem 4.C Speed vs Time');
% xlabel('Time(s)');
% ylabel('Speed');

% Part F
subplot(3,1,1);
plot(t,ia);
title('Problem 4.F Current vs Time');
xlabel('Time(s)');
ylabel('Current(A)');
subplot(3,1,2);
plot(t,omega);
title('Problem 4.F Speed vs Time');
xlabel('Time(s)');
ylabel('Speed');
subplot(3,1,3);
plot(t,Theta);
title('Problem 4.F Angle vs Time');
xlabel('Time(s)');
ylabel('Angle');