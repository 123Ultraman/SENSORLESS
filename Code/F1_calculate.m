U_dc = 300;
U1 = U_dc/sqrt(3);
U2 = 2/3*U_dc;
U3 = U_dc*2*sqrt(3)/3;

% 初始化F1和U_ref数组
U_ref = linspace(0, U3, 5000);
F1 = zeros(size(U_ref));
for i = 1:length(U_ref)
    U_ref_i = U_ref(i);
    if U_ref_i<=U1
        F1(i) = U_ref_i;
    elseif U1<U_ref_i&&U_ref_i<U2
        Temp1 = 1+sin(pi/6-(asin(U_dc/(sqrt(3)*U_ref_i))-pi/3));
        Temp2 = 1-sin(pi/6-(asin(U_dc/(sqrt(3)*U_ref_i))-pi/3));
        Temp3 = sqrt(3)*((asin(U_dc/(sqrt(3)*U_ref_i))-pi/3))*sqrt(3)*U_ref_i/U_dc;
        F1(i) = 2*U_dc/pi*(sqrt(3)/2*log(Temp1/Temp2)+Temp3);
    elseif U2<=U_ref_i&&U_ref_i<U3
        Temp1 = 1+sin(pi/6-(-asin(U_dc/(sqrt(3)*U_ref_i))+pi/3));
        Temp2 = 1-sin(pi/6-(-asin(U_dc/(sqrt(3)*U_ref_i))+pi/3));
        Temp3 = 2*sin(pi/3-asin(U_dc/(sqrt(3)*U_ref_i)));
        F1(i) = 2*U_dc/pi*(sqrt(3)/2*log(Temp1/Temp2)+Temp3);
    end

    if i>2
        if F1(i)<F1(i-1)
            F1(i)=F1(i-1)+0.00001;
        end
    end
end
plot(U_ref, F1);
xlabel('Uref');
ylabel('F1');
title('F1 vs Uref');
grid on;
clc;