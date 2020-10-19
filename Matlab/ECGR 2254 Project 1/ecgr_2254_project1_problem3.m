x_1 = [0];   %v
x_2 = [2];   %dv/dt

delta_t = 0.628/1000;  %628 micros
stop = round(5/delta_t);
t = [0:1:stop]*delta_t;

v_in = 5*cos(10*t+30*pi/180);

for n = 1:1:stop
    x_1(n+1) = x_2(n)*delta_t + x_1(n);
    x_2(n+1) = delta_t*(v_in(n) - 2*x_2(n) -4*x_1(n)) + x_2(n);
end

figure(1);
plot(t,x_1);
hold on;
title('Problem 3.C Voltage vs Time');
xlabel('Time(s)');
ylabel('Voltage(v)');

% The total Solution y(t)
y = (0.0190 - 0.4904j)*exp((-1+1.73j)*t) + (0.0190 + 0.4904j)*exp((-1-1.73j)*t) + .051*cos(10*t  - 138.2*pi/180);

plot(t,y,'color',[.5 .4 .7]) %plots with purple color
hold off;
grid on;

