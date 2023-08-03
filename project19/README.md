# Project19: forge a signature to pretend that you are Satoshi
## 一、实验思路
比特币中使用ECDSA进行签名，本次实验研究如何在未知明文消息m的前提下，伪造能通过检验的合法签名。<br>
ECDSA的密钥生成过程、签名过程以及检验过程如下图所示。利用sign函数与verify函数来实现。<br>
![ECDSA算法](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/3380522b-d180-40ea-9faa-8e7f07edb5c0)<br>
由于在Curve.py中我们已实现了椭圆曲线类的计算，且对运算符进行了定义，因此可以在代码中直接使用运算符来进行椭圆曲线上点与数的运算。<br>

如何进行签名的伪造呢？<br>

假设已经得到了真实且合法的签名(r,s)。<br>
在验证算法中，s^{-1}(eG+rP)=R=(x',y')，只需验证r=x' mod n是否成立。<br>
针对此过程，我们随机选择u,v，计算R'=(x',y')=uG+vP。<br>
当s'^{-1}(e'G+r'P)=uG+vP，计算得到(r',s',e')，这样就伪造得到可以通过验证的签名。<br>

## 二、运行结果
对消息“hello”进行签名得到正确签名，后进行伪造得到伪造签名，经验证发现伪造签名可以通过验证算法，伪造成功。<br>
![signatures_forge](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/b48ccc12-4b30-4433-babf-689be7085ee2)
