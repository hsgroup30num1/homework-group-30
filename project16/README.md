# Project16: implement sm2 2P decrypt with real network communication
## 一、实验思路
设计基于UDP协议的客户端client和服务端server以保证连接。
对需要双方参与的SM2解密，设置client作为解密发起方，server作为解密辅助方。<br>
在SM2_2P_decrypt_server.py文件中，服务端负责接收client发来的请求，生成并保存子私钥d2，计算并公开双方子私钥对应的公钥，需要辅助client进行解密，向client发送辅助的数据。<br>
在SM2_2P_decrypt_client.py文件中，客户端生成并保存子私钥d1，请求server辅助，针对利用server所公开公钥加密的密文进行解密。<br>
注意，以上两个python文件均需import pre_SM2，client还需import mySM2。
## 二、运行结果
先运行SM2_2P_decrypt_server.py文件建立连接<br>
再运行SM2_2P_decrypt_client.py文件，运行结果如下
![SM2_2P_decrypt_client](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/f8d56508-4aa4-4b0a-8658-36b8f45fe1da)
![SM2_2P_decrypt_server](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/47dba43f-4662-447a-88ad-099b50f22bbe)

