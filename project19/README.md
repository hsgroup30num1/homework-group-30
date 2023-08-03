# Project19: forge a signature to pretend that you are Satoshi
## 一、实验思路
比特币中使用ECDSA进行签名，本次实验研究如何在未知明文消息m的前提下，伪造能通过检验的合法签名。<br>
ECDSA的密钥生成过程、签名过程以及检验过程如下图所示。利用sign函数与verify函数来实现。<br>

由于在Curve.py中我们已实现了椭圆曲线类的计算，且对运算符进行了定义，因此可以在代码中直接使用运算符来进行椭圆曲线上点与数的运算。<br>
如何进行签名的伪造呢？<br>
假设已经得到了真实且合法的签名(r,s)。<br>
在验证算法中，s^{-1}(eG+rP)=R=(x\prime,y\prime)，只需验证r=x\primemod n是否成立。<br>
针对此过程，我们随机选择u,v，计算R'=(x',y')=uG+vP。<br>
当{s\prime}^{-1}(e\primeG+r\primeP)=uG+vP，计算得到(r',s',e')，这样就伪造得到可以通过验证的签名。<br>

## 二、运行结果
