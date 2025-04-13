H = ones(6, 2);
H(1,1) = mean(out.I_alpha1);
H(2,1) = mean(out.I_alpha2);
H(3,1) = mean(out.I_alpha3);
H(4,1) = mean(out.I_alpha4);
H(5,1) = mean(out.I_alpha5);
H(6,1) = mean(out.I_alpha6);
Z = ones(6, 1);
Z(1,1) = mean(out.U_alpha1);
Z(2,1) = mean(out.U_alpha2);
Z(3,1) = mean(out.U_alpha3);
Z(4,1) = mean(out.U_alpha4);
Z(5,1) = mean(out.U_alpha5);
Z(6,1) = mean(out.U_alpha6);
% Y = ones(6, 1);
% Y(1,1) = 3;
% Y(2,1) = 4;
% Y(3,1) = 5;
% Y(4,1) = 6;
% Y(5,1) = 7;
% Y(6,1) = 8;
Rs_hat = (H'*H)^(-1)*H'*Z;% 显示六个点
Rs_hat
figure;
plot(H(:,1), Z, 'o', 'MarkerSize', 8, 'MarkerFaceColor', 'b');
hold on; 
% 打印斜线
x = linspace(0, 1.1*max(H(:,1)), 100);
y = Rs_hat(1,1)*x + Rs_hat(2,1);
plot(x, y, 'r-', 'LineWidth', 2);
% 打印斜线方程
slope = Rs_hat(1,1);
intercept = Rs_hat(2,1);
text(min(H(:,1)) - 0.1*(max(H(:,1)) - min(H(:,1))), max(Z) + 0.1*(max(Z) - min(Z)), ...
     sprintf('y = %.2fx + %.2f', slope, intercept), ...
     'HorizontalAlignment', 'right', 'VerticalAlignment', 'top');
% 添加图例和标签
legend('Data Points', 'Fitted Line', 'location','northeast');
xlabel('I');
ylabel('U');
title('Motor Resistance Identification');