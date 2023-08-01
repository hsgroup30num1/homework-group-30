import random
import time
from gmssl import sm3, func

def Random(n): #生成2**(n/2)个不同的随机数
    LIST = []
    while len(LIST) < 2**(n/2):
        #假定sm3算法输入长度为32bits，大小为2**32-1
        i = random.randint(0, 2**32-1)
        if i not in LIST:
            LIST.append(i)
    return LIST

def brithAttack(n): #前n比特生日攻击判断是否存在碰撞
    global list1
    mydist={} #记录输入和对应的输出
    LIST=Random(n)
    for i in LIST:
        str = i.to_bytes(32 ,"big")
        result = sm3.sm3_hash(func.bytes_to_list(str))[:int(n / 4)]#取结果的前8bit
        if result not in mydist.values():
            mydist[i]=result
        else :
            list1.append((list(mydist.keys())[list(mydist.values()).index(result)],i))
            return True
    return False


sum1=0
sum2=0
sum3=0
list1=[]
start=time.time()
for i in range(1000):
    if brithAttack(int(8)):
        sum1+=1
end = time.time()
print('前8比特攻击成功率:',sum1/10,'%','耗时：',(end-start)/1000)
start=time.time()
for i in range(1000):
    if brithAttack(int(16)):
        sum2+=1
end = time.time()
print('前16比特攻击成功率:',sum2/10,'%','耗时：',(end-start)/1000)
for i in range(1000):
    if brithAttack(int(20)):
        sum3+=1
end = time.time()
print('前32比特攻击成功率:',sum3/10,'%','耗时：',(end-start)/1000)
# 开发时间：2023/7/31 12:12
