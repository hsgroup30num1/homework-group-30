#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "AES.h"
using namespace std;


//��ʼ��Կ
unsigned char key[16];


int main()
{

    ios::sync_with_stdio(false);

    cout << "���������ģ�";
    cin >> P;
    cout << "�������ʼ��Կ(���ֽ����룬��16���ֽ�.��'00 01 ... 0d 0e 0f')��";
    unsigned int xx;//��Ϊ���м��ˡ������û����뵥�ֽ���Կ
    for (int i = 0; i < 16; i++)  // ������Կ
    {
        cin >> hex >> xx;
        key[i] = xx;
    }

    cout << "��ԿΪ��" << endl;
    for (int i = 0; i < 16; i++) // ������Կ
    {
        printf("%02x  ", key[i]);
    }
    cout << "\n" << endl;

    KeyExpansion(key); //��Կ��չ

    cout << "����Ϊ:" << endl;
    for (int i = 0; i < strlen((char*)P); i++)
    {
        printf("%02x  ", P[i]);
    }

    cout << endl;
    encryption(); //����
    cout << endl;

    cout << "���ܺ������Ϊ:" << endl;
    for (int i = 0; i < strlen((char*)C); i++)
    {
        printf("%02x  ", C[i]);
    }
    cout << "\n" << endl;

    decryption();  //����

    cout << "���ܺ������Ϊ:" << endl;
    printf("%s\n", De_P);

    return 0;
}