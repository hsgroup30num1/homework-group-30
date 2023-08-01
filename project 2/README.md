# Project2: implement the Rho method of reduced SM3
## 一、实验思路
Rho算法是指定义一个函数，经过多次嵌套运算后会形成一个环，因其形状类似ρ而得名。通过Rho算法可以得到碰撞。<br>
实验思路如下：随机选取一个数i作为初始值并将其分别赋值给h1与h2，每次循环时分别将h1加密一次，将h2加密两次。当h1与h2前n比特产生碰撞时，分别记录其加密后的hash值，并计算产生碰撞所用时间。<br>
需要注意的是，通过比较发现函数x^2+1相较于x^2来说效率更高，因此本次实验中映射关系选择x^2+1。
## 二、运行结果
本次实验分别对前4比特、前8比特、前12比特以及前16比特进行Rho碰撞，运行结果如下。<br>
![rho1](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/4196b02a-3faa-4a35-a442-487d5bff0acd)
![rho2](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/85ef0caa-861d-4119-ba59-973f74e87029)
![rho3](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/386b85e1-7336-4483-a9bc-acef2b9d0b78)
![rho4](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/8e2f8526-2e60-4cb8-add1-e279f0c7d8cb)

## 三、实验结果
分析运行结果可知，随着需要碰撞的位数的增大，所需时间呈指数级增长（尤其长度大于16比特后），即碰撞所形成的圈呈指数级增大。
