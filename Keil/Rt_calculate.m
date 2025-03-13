T1 = 0:0.5:110;
format short e  % 科学计数法，4位小数
Rt = 10000*exp(3990*(1./(T1+273.15)-1/298.15));
Rt_ADCvaule = floor(4700./(4700 + Rt)*3.3/2.9*4096);
% 绘制曲线图
plot(T1, Rt);
% 添加标题和轴标签
title('Rt-T1');
xlabel('T1');
ylabel('Rt');

save('Rt.txt','Rt','-ascii');
save('T1.txt','T1','-ascii');
save('Rt_ADCvaule.txt','Rt_ADCvaule','-ascii');