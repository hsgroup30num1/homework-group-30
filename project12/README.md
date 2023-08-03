# Project12: verify the above pitfalls with proof-of-concept code
## 一、实验思路
通过编写代码，证明数字签名算法中存在部分缺陷。ECDSA、Schnorr、SM2三种签名算法中可能存在的安全隐患如下图所示。<br>
![pitfalls](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/3eef8d70-7ca7-4cdd-b2fc-86d512cc2d70)

## 二、代码说明
首先对椭圆曲线的参数进行选取。<br><br>
n = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123<br>
p = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF<br>
g_X = 0x32c4ae2c1f1981195f9904466a39c9948fe30bbff2660be1715a4589334c74c7<br>
g_Y = 0xbc3736a2f4f6779c59bdcee36b692153d0a9877cc62a474002df32e52139f0a0<br>
a = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC<br>
b = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93<br><br>
然后对三种签名算法可能存在的安全隐患进行测试，测试内容如下：<br>
1、泄露随机数k，推导出私钥。<br>
2、重用随机数k，推导出私钥。<br>
3、两个用户使用了同样的k，互相推导出对方的私钥。<br>
4、SM2与ECDSA算法使用相同的私钥d和随机数k，可以根据两组签名推导私钥。<br>
5、对称性，即(r,s)和(r,-s)都是合法的签名。调用验证算法验证(r,-s)是否能通过检测。<br>

## 三、运行结果
![signatures_pitfall](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/2b82dc2c-a235-4bb0-8e92-71ab9b010d7a)
分析运行结果可知，对于以上可能存在的安全隐患，均可正确推导出私钥并通过验证。因此数字签名算法中存在缺陷。
