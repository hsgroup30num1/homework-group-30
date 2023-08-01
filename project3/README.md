# Project3: implement length extension attack for SM3, SHA256, etc.
## 一、实验原理
对于基于Merkle–Damgård结构的算法，如MD5、SHA1、SHA2等，均存在以下问题：
在已知message与MAC的前提下，不需要已知key，只要知道key的长度，即可通过在message后添加信息计算来求得相应的MAC。
因此，如果攻击者掌握了Hash(message)的值与message的长度，就可以在不知道message的情况下得到Hash(message||padding||message1)的值。
以上便是长度扩展攻击的原理。<br>
## 二、实验思路
1、随机生成一个消息m<br>
2、对m进行SM3加密得到Hash<br>
3、随机生成一个附加消息m_append<br>
4、利用加密结束后的iv值作为初始向量，来加密m_append，得到hash猜测值<br>
5、将消息进行填充并添加附加消息后再次进行加密得到hash计算值<br>
6、比较hash猜测值与hash计算值，若相等，则攻击成功。<br>
## 三、运行结果
