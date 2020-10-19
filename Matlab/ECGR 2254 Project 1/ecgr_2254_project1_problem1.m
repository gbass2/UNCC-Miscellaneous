%Problem 1
figure(1)

R = 144; % Resistance
L = .00265; % Inductance, 2.65 mH
x_1 = [24.233];   %v
T = (2*pi)/377; % Period
delta_t = (L/R)/1000;  %16.67 millis
t = [0:delta_t:T];
stop = length(t);

v_in = 120*sqrt(2)*cos(377*t);

for n = 1:1:stop-1
    x_1(n+1) = delta_t*(-(R/L)*x_1(n) + v_in(n)/L) + x_1(n);
end

x_1=x_1*R;

plot(t,x_1)
title ('Problem 1.D Voltage vs Time');
grid on;
xlabel('Time (s)');
ylabel('Voltage (v)');

Vm = max(x_1)