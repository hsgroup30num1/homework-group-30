# Project10: report on the application of this deduce technique in Ethereum with ECDSA
## ECDSA
### 概述
椭圆曲线数字签名算法（ECDSA）是使用椭圆曲线密码（ECC）对数字签名算法（DSA）的模拟。
ECDSA于1999年成为ANSI标准，并于2000年成为IEEE和NIST标准。它在1998年既已为ISO所接受，并且包含它的其他一些标准亦在ISO的考虑之中。
与普通的离散对数问题（DLP）和大数分解问题（IFP）不同，椭圆曲线离散对数问题（ECDLP）没有亚指数时间的解决方法。
因此椭圆曲线密码的单位比特强度要高于其他公钥体制。<br>
ECDSA作为ECC与DSA的结合，整个签名过程与DSA类似，不同点是签名所采取的算法为ECC，最后得到的签名值为r，s。
### 签名过程
希望对消息m进行签名，选用椭圆曲线参数为D=（p,a,b,G,n,h），其中G为基点，n为G的阶；密钥对为（k,Q），其中k为私钥，Q为公钥，Q=kG。<br>
1、产生一个随机整数r（0<r<n）<br>
2、计算点R=rG=(x,y)<br>
3、计算H(m)=SHA1(m,x,y)<br>
4、计算s=r-H(m) * k (mod n)<br>
5、签名值为(r,s),注意r与s均不为0<br>
### 验证过程
验证方已知签名(r,s)，椭圆曲线参数D=（p,a,b,G,n,h），公钥Q，消息m。<br>
1、首先验证r与s均为区间[1,n-1]上的整数<br>
2、计算：sG+H(m)P=(x1,y1)，r1≡ x1 mod p<br>
3、验证等式：r1 ≡ r mod p<br>
4、当等式成立时，签名通过验证<br>
## Ethereum
以太坊（Ethereum）是一个开源的有智能合约功能的公共区块链平台，
通过其专用加密货币以太币（Ether，简称“ETH”）提供去中心化的以太虚拟机（Ethereum Virtual Machine）来处理点对点合约。
## 以太坊中ECDSA的应用
### 以太坊中ECDSA签名与验证
ECDSA 签名为(r,s)，在以太坊中还引入了额外的变量 v（恢复标识符），将签名表示成 (r, s, v)<br>
在创建签名时，你要先准备好一条待签署的消息，和用来签署该消息的私钥（dₐ）。简化后的签名流程如下：<br>
1.对待签署消息进行哈希计算，得到哈希值e。<br>
2.生成一个安全的随机数 k。<br>
3.将 k 乘以椭圆曲线的常量 G，来计算椭圆曲线上的点（x₁, y₁）。<br>
4.计算 r = x₁ mod n。如果 r 等于 0，请返回步骤 2 。<br>
5.计算 s = k⁻¹(e + rdₐ) mod n。如果 s 等于 0，请返回步骤 2。<br>
### 以太坊哪些地方使用了ECDSA？
在以太坊的交易过程中，如何认证某笔交易是否是由付款人发起的呢，这个环节就用到了ECDSA签名技术。简化的签名步骤如下:<br>
1.对交易数据进行 RLP 编码<br>
2.对第一步得到的编码进行哈希<br>
3.将哈希与标识以太坊的特定字符串拼接在一起，再次哈希。这一步是为了保证该签名仅在以太坊上可用<br>
4.用ECDSA算法对第三步得到的哈希进行签名，得到 (r, s, v)<br>
5.将第四步得到的签名与交易数据拼接，再次进行RLP编码，得到最终的签名消息。<br>
## 代码实现
选取椭圆曲线参数，运行ECDSA.py文件得到如下运行结果。
![ECDSA](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/aff6f9d9-cff4-4a24-ae7e-5b2bf092e6f5)
## 参考文献
[1]https://blog.csdn.net/weixin_43867940/article/details/130258535<br>
[2]https://blog.csdn.net/u013758702/article/details/121764374

