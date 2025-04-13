uiopen('F:\work\MOTOR_Control\SENSORLESS\Models\based_FOC.slx',1);
run('F:\work\MOTOR_Control\SENSORLESS\Code\F1_calculate.m');
uiopen('F:\work\MOTOR_Control\SENSORLESS\Models\ParameterIdentification.slx',1);
clc;
content = fileread('F:\work\MOTOR_Control\SENSORLESS\README.txt');  % 读取整个文件为一个字符串
disp(content);                      % 输出内容
