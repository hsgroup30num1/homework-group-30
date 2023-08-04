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
Project4: do your best to optimize SM3 implementation (software)<br>
Project5: Impl Merkle Tree following RFC6962<br>
Project9: AES / SM4 software implementation<br>
Project10: report on the application of this deduce technique in Ethereum with ECDSA<br>
Project11: impl sm2 with RFC6979<br>
Project12: verify the above pitfalls with proof-of-concept code<br>
Project13: Implement the above ECMH scheme<br>
Project14: Implement a PGP scheme with SM2<br>
Project15: implement sm2 2P sign with real network communication<br>
Project16: implement sm2 2P decrypt with real network communication<br>
Project19: forge a signature to pretend that you are Satoshi<br>
Project22: research report on MPT<br>

### （二）未完成project
Project6: impl this protocol with actual network communication<br>
Project7: Try to Implement this scheme<br>
Project8: AES impl with ARM instruction<br>
Project17：比较Firefox和谷歌的记住密码插件的实现区别<br>
Project18: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself<br>
Project21: Schnorr Bacth<br>

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

### Project3: implement length extension attack for SM3, SHA256, etc.
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project3

#### 实验思路
对于基于Merkle–Damgård结构的算法，如MD5、SHA1、SHA2等，均存在以下问题： 在已知message与MAC的前提下，不需要已知key，只要知道key的长度，即可通过在message后添加信息计算来求得相应的MAC。 因此，如果攻击者掌握了Hash(message)的值与message的长度，就可以在不知道message的情况下得到Hash(message||padding||message1)的值。<br>

对SM3的长度扩展攻击过程如下：<br>
1、随机生成一个消息m<br>
2、对m进行SM3加密得到Hash<br>
3、随机生成一个附加消息m_append<br>
4、利用加密结束后的iv值作为初始向量，来加密m_append，得到hash猜测值<br>
5、将消息进行填充并添加附加消息后再次进行加密得到hash计算值<br>
6、比较hash猜测值与hash计算值，若相等，则攻击成功。<br>

注意，在进行长度扩展攻击之前，需要对gmssl库中sm3的hash函数进行修改，主要操作包括添加参数iv用于传递向量<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“SM3的长度扩展攻击.py”<br>

#### 实验结果
随机生成一个消息，长度扩展攻击结果如下图所示。<br>
![长度扩展攻击](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/6565b3d6-8b8f-4e53-afa5-be5b00fa665a)

### Project4: do your best to optimize SM3 implementation (software)
https://github.com/hsgroup30num1/homework-group-30/tree/3c33af14c39439f2d13fd90e65ce3200872b9ec9/project4

#### 实验思路
根据SM3说明文档，编写SM3的各个基本组件。包括布尔函数、置换函数、消息扩展函数、压缩函数。<br>
本次实验通过宏定义、SIMD指令集以及算法优化等方法来实现对SM3的优化。具体优化思路如下。<br>

##### 布尔函数
优化：利用C语言的宏定义来代替函数，从而避免函数调用引起的开销。

##### 消息扩展函数
优化：利用128位的SIMD指令集同时处理多组数据。

##### 压缩函数
优化：<br>
1、利用C语言的宏定义来代替函数，从而避免函数调用引起的开销。<br>
2、循环展开<br>
分析压缩函数可知，轮函数共循环执行64次。分析可得这样迭代8次后，就会回到最初的情况。因此，可以将8次迭代作为一组，总共8组实现展开。<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：Visual Studio 2019<br>
运行方式：直接运行文件“main.cpp”<br>

#### 实验结果
对“abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd”进行SM3加密。<br>
由于单次运行时间较短，为了方便测算时间，我们重复进行1000000次SM3运算，运行结果如下:<br>
1000000次运算共耗时3.41s<br>
平均每次SM3运算耗时3.4μs<br>
由于每次运算512bit分组，因此吞吐率可达18.82MB/s<br>

### Project5: Impl Merkle Tree following RFC6962
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project5

#### 实验思路
Merkle Tree是一种哈希树，用于编码大块的信息。
其中每个叶子节点都标有数据块的加密哈希值，而每个非叶子节点都标有其子节点的加密哈希值的标签。
大多数哈希树的实现是二进制的（每个节点有两个子节点），但它们也可以有更多的子节点。
Merkle Tree的特别之处在于，这是一种自下而上建立的树，允许你验证某些值是否存在于树中，而不需要在树的每个元素上循环，这一特点非常有用。<br>

实验代码包括两部分：<br>
其一是头文件picosha.h，文件来源网络，用于实现sha256；<br>
其二是cpp文件MerkleTree，该文件实现MerkleTree的创建，同时可以用于确定某节点的哈希值以及判断给定哈希值的叶子节点是否存在于MerkleTree中。<br>

首先利用append函数添加5个叶子结点并自动生成如下图所示的MerkleTree，然后采用先序遍历进行打印并输出。<br>
![MerkleTree](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/3fa96a66-f42b-4a82-9a08-203ba0af4e58)
接下来我们验证“name”是否存在于Merkle Tree中。根据上图可知，我们需要提供阴影部分三个结点的哈希值。

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：Visual Studio 2019<br>
运行方式：直接运行文件“MerkleTree.cpp”<br>

#### 实验结果
![MerkleTree运行结果](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/26875848-c5d4-4c4e-aaa4-0f389af1f8a6)

### Project9: AES / SM4 software implementation
https://github.com/hsgroup30num1/homework-group-30/tree/dfaa5bf1dc4453cc40b8b363b5e68778c53fa051/project9

#### 实验原理
AES作为分组密码算法，分组长度为128bits，不同的密钥长度可满足不同的安全需求，根据常见密钥长度将其命名为“AES-128”、“AES-192”与“AES-256”。基本的算法构成包括加密算法、解密算法、密钥扩展算法。<br>

加密方案<br>

AES 加密算法共涉及 4 种操作：S盒（SubBytes）、行移位（ShiftRows）、列混合 （MixColumns）和轮密钥加（AddRoundKey）。<br>
首先对明文与原始密钥进行依次异或操作，从而避免不用密钥即可完成逆过程的可能，保证算法的安全性。<br>
然后进行10轮迭代加密，每一轮包括以下四个操作：字节代换，行移位，列混合，轮密钥加。注意最后一轮迭代不执行列混合操作。<br>

解密方案<br>

AES 解密算法的每一步分别对应加密算法的逆操作。加解密所有操作的顺序正好是相 反的，每轮的密钥分别由种子密钥经过密钥扩展算法得到。<br>
首先对密文进行一次轮密钥加操作。<br>
然后进行10轮迭代加密，每一轮顺序执行以下四个操作：逆行移位，逆字节代换，逆轮密钥加，逆列混合。注意最后一轮迭代不执行逆列混合操作。<br>

密钥扩展方案<br>

密钥扩展的复杂性是确保算法安全性的重要部分。AES-128的密钥扩展需将128bits的密钥扩展为11个轮密钥，即44个32bits密钥字。<br>
AES首先将初始密钥写到4*4矩阵中，每一列为一个32bits字，依次记为W_0，W_1，W_2，W_3。然后对W数组进行扩充得到44列即44个32bits字。扩充算法如下：<br>
对每个轮密钥的第一列W_i,由如下等式确定：W_i=W_{i-4}\bigoplusT（Wi-1），其中T函数由以下3部分构成：循环移位、字节代换、异或轮常量。W_{i-1}循环移位一个字节后经过S盒进行字节代换，得到的结果异或轮常数。<br>
对每个轮密钥除第一列外的其余三列W_i,由如下等式确定：W_i=W_{i-4}\bigoplus W_{i-1}.<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：Visual Studio 2019<br>
运行方式：直接运行文件“main.cpp”<br>

#### 实验结果
![AES](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/c395dd8c-2505-4416-b11c-478413ea2b64)

### Project10: report on the application of this deduce technique in Ethereum with ECDSA
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project10

#### 实验思路
要研究ECDSA在以太坊中的应用，我们首先对ECDSA与以太坊的概念进行解析。<br>

ECDSA椭圆曲线数字签名算法是使用椭圆曲线密码（ECC）对数字签名算法（DSA）的模拟，整个签名过程与DSA类似，不同点是签名所采取的算法为ECC，最后得到的签名值为r，s。<br>

ECDSA签名过程如下：<br>
希望对消息m进行签名，选用椭圆曲线参数为D=（p,a,b,G,n,h），其中G为基点，n为G的阶；密钥对为（k,Q），其中k为私钥，Q为公钥，Q=kG。<br>
1、产生一个随机整数r（0<r<n）<br>
2、计算点R=rG=(x,y)<br>
3、计算H(m)=SHA1(m,x,y)<br>
4、计算s=r-H(m) * k (mod n)<br>
5、签名值为(r,s),注意r与s均不为0<br>

ECDSA验证过程如下：<br>
验证方已知签名(r,s)，椭圆曲线参数D=（p,a,b,G,n,h），公钥Q，消息m。<br>
1、首先验证r与s均为区间[1,n-1]上的整数<br>
2、计算：sG+H(m)P=(x1,y1)，r1≡ x1 mod p<br>
3、验证等式：r1 ≡ r mod p<br>
4、当等式成立时，签名通过验证<br>

以太坊（Ethereum）是一个开源的有智能合约功能的公共区块链平台，
通过其专用加密货币以太币（Ether，简称“ETH”）提供去中心化的以太虚拟机（Ethereum Virtual Machine）来处理点对点合约。<br>

在以太坊的交易过程中，如何认证某笔交易是否是由付款人发起的呢，这个环节就用到了ECDSA签名技术。简化的签名步骤如下:<br>
1.对交易数据进行 RLP 编码<br>
2.对第一步得到的编码进行哈希<br>
3.将哈希与标识以太坊的特定字符串拼接在一起，再次哈希。这一步是为了保证该签名仅在以太坊上可用<br>
4.用ECDSA算法对第三步得到的哈希进行签名，得到 (r, s, v)<br>
5.将第四步得到的签名与交易数据拼接，再次进行RLP编码，得到最终的签名消息。<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“ECDSA.py”<br>

#### 实验结果
选取椭圆曲线参数后，运行上述python文件可以得到如下结果。
![ECDSA](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/4c8c4f2c-ca6b-4d4c-8e1b-bb2285cf2d96)

### Project11: impl sm2 with RFC6979
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project11

#### 实验思路
SM2椭圆曲线公钥密码算法的实现，重点在加密与解密算法。<br>

SM2加密如下：<br>
1、用随机数发生器产生随机数k (1<k<n-1)<br>
2、计算椭圆曲线点C1=[k]G=(x1,y1)，并将其转换为比特串（A的私钥生成公钥）<br>
3、计算椭圆曲线点S=[h]Pb，若S是无穷远点，则报错并退出 h为n的余因子<br>
4、计算椭圆曲线点[k]Pb=(x2,y2)，并将其转换为比特串（A的私钥乘B的公钥）<br>
5、计算t=KDF(x2||y2,klen)，若t为全0比特串，则返回①; KDF为密钥派生函数<br>
6、计算C2=M⊕t<br>
7、计算C3=Hash(x2||M||y2)<br>
8、输出密文C=C1||C3||C2<br>

SM2解密如下：<br>
1、从C中取出比特串C1，将其转换为椭圆曲线上的点，验证C1是否满足椭圆曲线方程<br>
2、计算椭圆曲线点S=[h]Pb，若S是无穷远点，则报错并退出<br>
3、计算[db]C1=(x2,y2)，并将其转换为比特串 db B的公钥<br>
4、计算t=KDF(x2||y2,klen)，若t为全0比特串，则返回（一） KDF为密钥派生函数<br>
5、从C中取出比特串C2,计算M=C2⊕t<br>
6、计算u=Hash(x2||M||y2)，从C中取出比特串C3，若u不等于C3，则报错并退出<br>
7、输出明文M<br>

本次实验共用到以下两个文件：<br>
pre_SM2.py：适用于SM2的前置算法。包含SM2的系统参数以及一些运算（椭圆曲线上点加、逆元、点减、点乘等）<br>
mySM2.py：用于实现SM2，需要用到pre_SM2.py。运行时先生成一对公私钥，然后利用公钥对消息进行加密，利用私钥对消息进行解密。

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“mySM2.py”<br>

#### 实验结果
输入明文“Hello my name is xxx”，利用SM2加密输出密文c，解密输出明文m。
![SM2](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/c3fc5308-9e8f-42de-ae52-bb90ae6c6b51)

### Project12: verify the above pitfalls with proof-of-concept code
https://github.com/hsgroup30num1/homework-group-30/tree/860460e7d37eb3e126aa7dfc6f5bd4e9f5fa3b58/project12

#### 实验思路
通过编写代码，证明数字签名算法中存在部分缺陷。<br>
实验代码包括两部分：signatures_pitfall.py以及它所import的Curve.py<br>

首先对椭圆曲线的参数进行选取。<br>
然后对三种签名算法可能存在的安全隐患进行测试，测试内容如下：<br>

1、泄露随机数k，推导出私钥。<br>
2、重用随机数k，推导出私钥。<br>
3、两个用户使用了同样的k，互相推导出对方的私钥。<br>
4、SM2与ECDSA算法使用相同的私钥d和随机数k，可以根据两组签名推导私钥。<br>
5、对称性，即(r,s)和(r,-s)都是合法的签名。调用验证算法验证(r,-s)是否能通过检测。<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“signatures_pitfall.py”<br>

#### 实验结果
运行结果如下：<br>
![signatures_pitfall](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/777e07e8-6638-4c40-a3cd-12024c9d334c)
分析运行结果可知，对于以上可能存在的安全隐患，均可正确推导出私钥并通过验证。因此数字签名算法中存在缺陷。

### Project13: Implement the above ECMH scheme
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project13

#### 实验思路
ECMH的中心思想为将元素hash映射成椭圆曲线上的点后，利用椭圆曲线上的加法添加信息并将信息存储在集合中，后将集合中每一个元素的hash映射成椭圆曲线上的点。<br>
由于重复的相同元素会产生不同的签名，因此将hash=(b"hello",b"hello")带入hashmul函数进行计算。理想的实验结果为二者产生的hash不同。

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“ECMH.py”<br>

#### 实验结果
![ECMH](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/d3785867-371c-40b7-b29e-6206f848580e)

### Project14: Implement a PGP scheme with SM2
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project14

#### 实验思路
PGP（Pretty Good Privacy）是个混合加密算法，它由一个对称加密算法（IDEA）、一个非对称加密算法（RSA）、与单向散列算法（MD5）
以及一个随机数产生器（从用户击键频率产生伪随机数序列的种子）组成<br>
主要思路即利用公钥密码来加密密钥，利用对称密码来加密明文。<br>

加密过程：<br>
1、随机选取密钥k<br>
2、利用公钥来加密k，并发送给接收者（SM2）<br>
3、利用密钥k来加密明文（DES）<br>

解密过程：<br>
1、接收者利用私钥解密码得到k<br>
2、利用密钥k来解密密文<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“SM2_PGP.py”<br>

#### 实验结果
![SM2_PGP](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/41a2f024-040d-424b-944d-09c30c0d9a0c)

### Project15: implement sm2 2P sign with real network communication
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project15

#### 实验思路
对需要双方参与的SM2签名，设置client作为签名发起方，server作为签名辅助方。<br>

在SM2_2P_sign_server.py文件中，服务端负责接收client发来的请求，生成并保存子私钥d2，需要辅助client进行签名，向client发送辅助的数据。<br>
在SM2_2P_sign_client.py文件中，客户端生成并保存私钥d1，请求server辅助完成签名。<br>
注意，以上两个python文件均需import pre_SM2。

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：先运行SM2_2P_sign_server.py文件建立连接。再运行SM2_2P_sign_client.py文件。<br>

#### 实验结果
运行SM2_2P_sign_client.py后，SM2_2P_sign_client.py的运行结果如下：
![SM2_2P_sign_client](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/533eba29-179e-4797-ba71-f98b2fd1c591)

SM2_2P_sign_server.py的运行结果如下：
![SM2_2P_sign_server](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/ba25bb8c-496f-499d-9d9e-5c95af83c2f5)

### Project16: implement sm2 2P decrypt with real network communication
https://github.com/hsgroup30num1/homework-group-30/tree/e68182da6df575215c79e028ad0990cdf6808271/project16

#### 实验思路
对需要双方参与的SM2解密，设置client作为解密发起方，server作为解密辅助方。<br>

在SM2_2P_decrypt_server.py文件中，服务端负责接收client发来的请求，生成并保存子私钥d2，计算并公开双方子私钥对应的公钥，需要辅助client进行解密，向client发送辅助的数据。<br>
在SM2_2P_decrypt_client.py文件中，客户端生成并保存子私钥d1，请求server辅助，针对利用server所公开公钥加密的密文进行解密。<br>
注意，以上两个python文件均需import pre_SM2，client还需import mySM2。

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：先运行SM2_2P_decrypt_server.py文件建立连接，再运行SM2_2P_decrypt_client.py文件。<br>

#### 实验结果
运行SM2_2P_decrypt_client.py后，SM2_2P_decrypt_client.py的运行结果如下：
![SM2_2P_decrypt_client](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/f93c5d1a-456a-43b8-94b6-b613ff42e66d)

SM2_2P_decrypt_server.py的运行结果如下：
![SM2_2P_decrypt_server](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/734458b0-c844-434f-abea-46b14f772344)

### Project19: forge a signature to pretend that you are Satoshi
https://github.com/hsgroup30num1/homework-group-30/tree/4665a38c765268ab11c93a684d75a9bc678d220e/project19

#### 实验思路
比特币中使用ECDSA进行签名，本次实验研究如何在未知明文消息m的前提下，伪造能通过检验的合法签名。<br>
本次实验代码包括两部分，除signatures_forge.py外，还包括Curve.py文件，用于实现椭圆曲线类的计算，对运算符进行了定义，使我们在signatures_forge.py中可以直接使用运算符来进行椭圆曲线上点与数的运算。<br>

如何进行签名的伪造呢？<br>

假设已经得到了真实且合法的签名(r,s)。<br>
在验证算法中，s^{-1}(eG+rP)=R=(x',y')，只需验证r=x' mod n是否成立。<br>
针对此过程，我们随机选择u,v，计算R'=(x',y')=uG+vP。<br>
当s'^{-1}(e'G+r'P)=uG+vP，计算得到(r',s',e')，这样就伪造得到可以通过验证的签名。<br>

#### 运行指导
硬件环境：AMD Ryzen 7 4800H with Radeon Graphics            2.90 GHz<br>
软件环境：PyCharm Community Edition 2022.2.2<br>
运行方式：直接运行文件“signatures_forge.py”<br>

#### 实验结果
对消息“hello”进行签名得到正确签名，后进行伪造得到伪造签名，经验证发现伪造签名可以通过验证算法，伪造成功。<br>
![signatures_forge](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/f6280f2c-ff25-4fac-ba54-201b77636d6c)

### Project22: research report on MPT
https://github.com/hsgroup30num1/homework-group-30/tree/99f8723091936f502d94df7ecb78f473c1c27b4b/project22

MPT (Merkle Patricia Tries) 是以太坊存储数据的核心数据结构，它是由 Merkle Tree 和 Patricia Tree 结合所组成的一种树形结构，理解 MPT 有助于帮助我们更好的理解以太坊的数据存储。<br>
首先我们介绍基本的Trie Tree 结构和 Merkle Tree、Patricia Tree这两种特殊结构，在此基础上我们研究MPT的结构特点及其优点与应用。<br>

#### Trie Tree
TrieTree，又称字典树或前缀树，是一种有序树，典型应用是用于统计，排序和保存大量的字符串。其核心思想就是用空间换时间，利用公共前缀缩小要比较的范围来达到快速查找的目的。相比于哈希表，使用前缀树来进行查询拥有共同前缀key的数据时十分高效。但也存在一定的缺陷，当存在少量的长字符串，且某个较长前缀下只有本身一个元素时，树的高度会很大，且一条长路径上只有一个叶节点。这样极大地浪费存储空间，且应用起来效率也不高。

#### Patricia Tree
压缩前缀树，是一种更节省空间的 Trie Tree。对于树的每个节点，如果该节点是唯一的子节点，就和父节点合并。

#### Merkle Tree
Merkle Tree是一种哈希树，用于编码大块的信息。 其中每个叶子节点都标有数据块的加密哈希值，而每个非叶子节点都标有其子节点的加密哈希值的标签。Merkle Tree的特别之处在于，这是一种自下而上建立的树，允许你验证某些值是否存在于树中，而不需要在树的每个元素上循环，这一特点非常有用。

#### MPT
MPT，即Merkle Patricia Tree。是一种经过改良的、融合了默克尔树和前缀树两种树结构优点的数据结构，是以太坊中用来组织管理账户数据、生成交易集合哈希的重要数据结构。MPT树中的节点包括空节点、叶子节点、扩展结点和分支节点。接下来从MPT的作用、结构特点、设计目的、优点以及应用等角度进行详细阐述。
