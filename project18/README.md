# Project18: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself
## 实验思路
本次实验共完成以下三个任务：<br>
- 在bitcoin testnet上创建钱包。<br>
- 申请一定数量的bitcoin并自己在测试网上提交一笔交易。<br>
- 编写脚本对提取的交易的原始数据进行解析。<br>

首先进入网站www.bitaddress.org，该网站可以通过键盘输入随机字符或者读取鼠标运动轨迹来生成一个地址及其对应的私钥。当进度达到100%时可以得到结果。<br>
分析所得结果可知，左边的字符串是创建的地址，右边是私钥。有了这个地址后，我们就可以在网络上申请一些测试用的比特币到这个地址中。如果我们需要使用这些比特币，则应使用对应的私钥提取出来。<br>

接下来进入网站https://bitcoinfaucet.uo1.net 获取测试用币。在该网站中，一个IP可以申请到至多0.00072个可在testnet中使用的比特币。<br>
我们输入刚刚生成的地址，点击申请获得比特币。到此为止，我们已经成功地取得了一些可用的比特币。<br>

在网站https://live.blockcypher.com/btc-testnet 中可以查看testnet上进行的所有交易。通过API Call可以查看详细的交易JSON数据，提取出这些数据。<br>

通过analysis可得：交易地址即为创建的测试地址，其中包含hash值，交易的地址，交易的总数，给矿工的费用，收到的时间，input（其中有签名，并且指向使用哪个交易的output），output（包含value也包含了接收方的地址）。
