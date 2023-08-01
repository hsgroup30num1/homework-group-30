# Project15: implement sm2 2P sign with real network communication
## 一、实验思路
设计基于UDP协议的客户端client和服务端server以保证连接。
对需要双方参与的SM2签名，设置client作为签名发起方，server作为签名辅助方。<br>
在SM2_2P_sign_server.py文件中，服务端负责接收client发来的请求，生成并保存子私钥d2，需要辅助client进行签名，向client发送辅助的数据。<br>
在SM2_2P_sign_client.py文件中，客户端生成并保存私钥d1，请求server辅助完成签名。<br>
注意，以上两个python文件均需import pre_SM2。
## 二、运行结果
先运行SM2_2P_sign_server.py文件建立连接。<br>
再运行SM2_2P_sign_client.py文件，此时client与server的运行结果如下。
![SM2_2P_sign_client](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/d9b46200-c1a2-4316-9613-29c0d8790740)
![SM2_2P_sign_server](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/a5954763-dc74-43a8-9569-432a5998c48c)
