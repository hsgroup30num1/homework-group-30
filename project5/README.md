# Project5: Impl Merkle Tree following RFC6962
## 一、实验原理
Merkle Tree是一种哈希树，用于编码大块的信息。
其中每个叶子节点都标有数据块的加密哈希值，而每个非叶子节点都标有其子节点的加密哈希值的标签。
大多数哈希树的实现是二进制的（每个节点有两个子节点），但它们也可以有更多的子节点。
Merkle Tree的特别之处在于，这是一种自下而上建立的树，允许你验证某些值是否存在于树中，而不需要在树的每个元素上循环，这一特点非常有用。
## 二、实验思路
实验代码包括两部分：
其一是头文件picosha.h，文件来源网络，用于实现sha256；
其二是cpp文件MerkleTree，该文件实现MerkleTree的创建，同时可以用于确定某节点的哈希值以及判断给定哈希值的叶子节点是否存在于MerkleTree中。<br>
首先利用append函数添加5个叶子结点并自动生成如下图所示的MerkleTree，然后采用先序遍历进行打印并输出。<br>
![MerkleTree](https://github.com/hsgroup30num1/homework-group-30/assets/129477640/f0757fd7-a40f-4060-8319-df01439e4c2c)
接下来我们验证“name”是否存在于Merkle Tree中。根据上图可知，我们需要提供阴影部分三个结点的哈希值。
## 三、运行结果
