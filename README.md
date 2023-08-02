# 创新创业实践课程汇总报告
## 一、成员分工
### 姓名：韩舒 
### 学号：202100460068
未组队，所有project均一人完成。
## 二、项目完成情况
### （一）已完成project
Project1: implement the naïve birthday attack of reduced SM3<br>
Project2: implement the Rho method of reduced SM3<br>
Project3: implement length extension attack for SM3, SHA256, etc.<br>
Project5: Impl Merkle Tree following RFC6962<br>
Project10: report on the application of this deduce technique in Ethereum with ECDSA<br>
Project11: impl sm2 with RFC6979<br>
Project13: Implement the above ECMH scheme<br>
Project14: Implement a PGP scheme with SM2<br>
Project15: implement sm2 2P sign with real network communication<br>
Project16: implement sm2 2P decrypt with real network communication<br>
### （二）未完成project
Project4: do your best to optimize SM3 implementation (software)<br>
Project6: impl this protocol with actual network communication<br>
Project7: Try to Implement this scheme<br>
Project8: AES impl with ARM instruction<br>
Project9: AES / SM4 software implementation<br>
Project12: verify the above pitfalls with proof-of-concept code<br>
Project17：比较Firefox和谷歌的记住密码插件的实现区别<br>
Project18: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself<br>
Project19: forge a signature to pretend that you are Satoshi<br>
Project21: Schnorr Bacth<br>
Project22: research report on MPT<br>
## 三、project具体实现

### Project1: implement the naïve birthday attack of reduced SM3
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project%201
#### 实验思路
生日攻击基于生日悖论，即如果一个房间里有23个或23个以上的人，那么至少有两人生日相同的概率大于50%。随着消息空间的增大，能以较大概率在消息空间中找到碰撞。对SM3前n比特进行生日攻击，消息空间（即输入）为2的二分之n次方，我们可以检测碰撞，并通过多次实验计算成功率与所需时间。<br>
我们分别取前8比特、前16比特、前32比特进行生日攻击，各自循环1000次来计算成功率与所需时间。
#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“SM3的生日攻击.py”<br>
#### 实验结果
前n比特    |成功率    |所需时间
---------------|---------------------------|-------------------------------
8	|36.1%	|0.008392898797988891
16	|39.1%	|0.07742399787902832
32	|43.6%	|0.38705969548225405

通过比较可知，随位数增加，消息空间增大，碰撞发生的可能性增大，即生日攻击成功率提高；但同时会导致所需时间增长，攻击速度变慢。

### Project2: implement the Rho method of reduced SM3
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project%202
#### 实验思路
Rho算法的核心思想即不必逐个寻找碰撞，而是“跳着”求，经过多次嵌套运算后形成一个环即形成碰撞。<br>
在实现过程中，我们随机选取一个数i作为初始值并将其分别赋值给h1与h2，每次循环时分别将h1加密一次，将h2加密两次。当h1与h2前n比特产生碰撞时，分别记录其加密后的hash值，并计算产生碰撞所用时间。需要注意的是，通过比较发现函数x^2+1相较于x^2来说效率更高，因此本次实验中映射关系选择x^2+1。<br>
我们分别对前4比特、前8比特、前12比特以及前16比特进行Rho碰撞。
#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“SM3的Rho碰撞.py”<br>
#### 实验结果
前n比特    |4    |8    |12    |16
--------------------|--------------------|--------------------|--------------------|--------------------|
所需时间	|0.03538632392883301	|0.01819586753845215	|0.6120591163635254	|8.536427736282349

通过比较可知，随着需要碰撞的位数的增大，所需时间呈指数级增长（尤其长度大于16比特后），即碰撞所形成的圈呈指数级增大。

