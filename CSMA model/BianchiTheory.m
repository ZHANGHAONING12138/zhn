clc;
clear all;
close all;                
global W m n
%Initialization
W = 2;                      %Initial window size
N = 100;                     %Number of users
m = 10;                     %Numer of stages
Pc1=[];
Tau_m1=[];
Throughput1=[];

Packetpayload = 512*8;       %bits
DIFS = 128;                 %us
SIFS = 28;                  %us
slot = 50;                  %us
dataRate = 1;               %Mbps
MAC = 272;                  %bits
PHY = 128;                  %bits
propdelay = 1;              %us
ACK = (112 + PHY) / dataRate;       
H = (PHY + MAC) / dataRate;  
EP = Packetpayload / (dataRate*slot);  
%Calculation:Pc, tau, throughput
for n = 1:N;
Output1 = fsolve(@myfun1,[0 0]',optimset('Display','off'));
p1 = Output1(1);            %Pcollision
tau1 = Output1(2);          %Pone-node success
Pc1 = [Pc1 p1];
Tau_m1 = [Tau_m1 tau1];

Ptr1 = 1 - (1 - tau1) ^ n;
Ps1 = n * tau1 * (1 - tau1) ^ (n-1) / Ptr1;
% Ts1 = (H + EP + SIFS + propdelay + ACK + DIFS + propdelay)/slot;
% Tc1 = (H + EP + DIFS + propdelay)/slot;
Ts1 = EP + ((H + SIFS + propdelay + ACK + DIFS + propdelay)/slot);
Tc1 = EP + ((H + DIFS + propdelay)/slot);
EPHI1 = (1 / Ptr1) - 1;
Th_temp1 = (Ps1 * EP) / (EPHI1 + Ps1 * Ts1 + (1 - Ps1) * Tc1);
Throughput1=[Throughput1 Th_temp1];     %Saturation throughput
end
%Change initial window size and number of stages
W = 63;
m = 2;
Pc2=[];
Tau_m2=[];
Throughput2=[];

for n = 1:N;
Output2 = fsolve(@myfun1,[0 0]',optimset('Display','off'));
p2 = Output2(1);
tau2 = Output2(2);
Pc2 = [Pc2 p2];
Tau_m2 = [Tau_m2 tau2];

Ptr2 = 1 - (1 - tau2) ^ n;
Ps2 = n * tau2 * (1 - tau2) ^ (n-1) / Ptr2;
% Ts2 = (H + EP + SIFS + propdelay + ACK + DIFS + propdelay)/slot;
% Tc2 = (H + EP + DIFS + propdelay)/slot;
Ts2 = EP + ((H + SIFS + propdelay + ACK + DIFS + propdelay)/slot);
Tc2 = EP + ((H + DIFS + propdelay)/slot);
EPHI2 = (1 / Ptr2) - 1;
Th_temp2 = (Ps2 * EP) / (EPHI2 + Ps2 * Ts2 + (1 - Ps2) * Tc2);
Throughput2 = [Throughput2 Th_temp2];
end

%Additional temporary case
W = 2;
m = 2;
Pc3=[];
Tau_m3=[];
Throughput3=[];

for n = 1:N;
Output3 = fsolve(@myfun1,[0 0]',optimset('Display','off'));
p3 = Output3(1);
tau3 = Output3(2);
Pc3 = [Pc3 p3];
Tau_m3 = [Tau_m3 tau3];

Ptr3 = 1 - (1 - tau3) ^ n;
Ps3 = n * tau3 * (1 - tau3) ^ (n-1) / Ptr3;
%Ts3 = H + EP + SIFS + propdelay + ACK + DIFS + propdelay;
%Tc3 = H + EP + DIFS + propdelay;
Ts3 = EP + ((H + SIFS + propdelay + ACK + DIFS + propdelay)/slot);
Tc3 = EP + ((H + DIFS + propdelay)/slot);
Th_temp3 = (Ps3 * Ptr3 * EP) / (Ptr3 * Ps3 * Ts3 + Ptr3 * (1 - Ps3) * Tc3 + 1 - Ptr3);
Throughput3 = [Throughput3 Th_temp3];
end

%Plot together
figure('name','Probability of collision ');
%plot(1:N,Pc1,1:N,Pc2,1:N,Pc3,'linewidth',3);
plot(1:N,Pc1,1:N,Pc2,'linewidth',3);
title('Pcollision VS Number of users');
xlabel('Number of nodes');
ylabel('Pcollision');
hold on;
grid on;
%plot(1:N,Pc2,'linewidth',3);
LEGEND = legend('Wmin=1&m=10','Wmin=63&m=2','Wmin=1&m=2');
set(LEGEND, 'Position', [0.213690479596455 0.826587316027236 0.18749999659402 0.0869047596341087]);
set(LEGEND,'Units','Normalized','FontUnits','Normalized')


figure('name','Saturation throughput');
%plot(1:N,Throughput1,1:N,Throughput2,1:N,Throughput3,'linewidth',2);
plot(1:N,Throughput1,1:N,Throughput2,'linewidth',3);
%plot(10:N,Throughput1(10:100),10:N,Throughput2(10:100),'linewidth',3);
title('Total Throughput VS Number of users');
ylabel('Th(total,Mbps)');
xlabel('Numbers of nodes');
grid on;
hold on;
%plot(1:N,Throughput2,'linewidth',3);
legend('Wmin=1&m=10','Wmin=63&m=2','Wmin=1&m=2');

% SimuTh1=[0.5827 0.5040 0.4603 0.4488 0.4390 0.3720 0.3653 0.3576 0.3614 0.3403];
% SimuTh2=[0.7445 0.7574 0.7450 0.7399 0.7300 0.7363 0.7156 0.7156 0.7108 0.6998];
% plot(10:10:N,SimuTh1,10:10:N,SimuTh2,'linewidth',3);
%legend('Wmin=1&Wmax=1023(THEORY)','Wmin=63&Wmax=127(THEORY)','Wmin=1&Wmax=1023(SIMULATION)','Wmin=63&Wmax=127(SIMULATION)');