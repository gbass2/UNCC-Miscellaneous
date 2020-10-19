Rs = .262;
R2 = .187;
X1 = 1.206;
X2 = 1.206;
Xm = 54.02;

beta = .2565;
J = 63.87;
x_1 = [0]; 

delta_t = .001;  % Given value
stop = 10000;
t = [0:1:stop]*delta_t;


for n = 1:1:stop
    % Finding the value for slip
    slip = (2*pi*30 - x_1(n))/(2*pi*30);
    
    % Calculating the matrix for I_1 and I_2
    a = [(Rs + j*X1 + j*Xm) -j*Xm; -j*Xm (j*X2 + (R2/slip) + j*Xm)];
    b = [2300; 0];
    x = inv(a)*b;
    
    % Assigning I_1 and I_2 to their respective elements
    I_1 = x(1,:);
    I_2 = x(2,:);
    mag_I1(n+1) = abs(I_1);
    mag_I2 = abs(I_2);
    
    
    % Computing the Torque
    T_m = ((3*(mag_I2)^2)*(R2/slip))/(2*pi*30);
    ohm_in = T_m/J;
    
    % Solving for ohm(t)
    x_1(n+1) = delta_t*(ohm_in - (beta*((x_1(n))^2))/J) + x_1(n);
end

figure(1);

% plot for ohm(t)
subplot(2,1,1);
plot(t, x_1);
ylabel('ohm(t):rad/sec');
title('Problem 5');
grid on;

% Plot for the magnitude of I1
subplot(2,1,2);
plot(t,mag_I1);
ylabel('|I_1|:A');
xlabel('Time:sec');
grid on;
