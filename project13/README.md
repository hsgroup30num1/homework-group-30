# Project13: Implement the above ECMH scheme
## 一、实验原理
ECMH的中心思想为将元素hash映射成椭圆曲线上的点后，利用椭圆曲线上的加法添加信息并将信息存储在集合中，后将集合中每一个元素的hash映射成椭圆曲线上的点。
## 二、代码说明
由于重复的相同元素会产生不同的签名，因此将hash=(b"hello",b"hello")带入hashmul函数进行计算。理想的实验结果为二者产生的hash不同。
## 三、运行结果
![ECMH](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/4a8720d6-79d0-4f3a-a90e-3a1422c11d0a)
