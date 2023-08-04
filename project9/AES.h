#pragma once
#include <iostream>
using namespace std;

#ifndef _AES_H_
#define _AES_H_

// S��
extern unsigned char S[256];

//��S��
extern unsigned char inv_S[256];

// AES-128�ֳ���
static const unsigned int rcon[10] = {
    0x01000000UL, 0x02000000UL, 0x04000000UL, 0x08000000UL, 0x10000000UL,
    0x20000000UL, 0x40000000UL, 0x80000000UL, 0x1B000000UL, 0x36000000UL
};

//�л���ʱ�õ���������
extern unsigned char positive_matrix[4][4];

//���л���ʱ�õ�����������
extern unsigned char inv_positive_matrix[4][4];

//��Կ��չ
extern unsigned int W[44];

//���������ĵ���󳤶�
static const int MAX_LENGTH = 1e6;

//����
extern unsigned char P[MAX_LENGTH];
//����֮�������
extern unsigned char De_P[MAX_LENGTH];
//������128����
extern unsigned char P128[16];

//����
extern unsigned char C[MAX_LENGTH];
//������128����
extern unsigned char C128[16];

//��128����ת��Ϊ״̬����
void array_to_mat(unsigned char p[], unsigned char state_mat[][4]);

//��״̬����ת��Ϊ128����
void mat_to_array(unsigned char state_mat[][4], unsigned char c[]);

//��1��32λ����Կ��ת��Ϊ4��8λ��Կ
void key32_to_key8(unsigned int key32, unsigned char* key8);

//��4��8λ����Կ��ת��Ϊ1��32λ��Կ
unsigned int key8_to_key32(unsigned char* key8);

//�ֽ��滻
unsigned char SubBytes(unsigned char input);

//��λ��
void ShiftRows(unsigned char state_mat[][4]);

//�������ϵĳ˷�
unsigned char multi_finite_field(unsigned char a, unsigned char b);

//�л��
void MixColumns(unsigned char state_mat[][4]);

//����Կ�ӣ�cnt������ǵڼ���ѭ��
void AddRoundKey(unsigned char state_mat[][4], int cnt);

//��Կ��չʱ��T������cnt��������
unsigned int T(unsigned int input, int cnt);

//��Կ��չ����
void KeyExpansion(unsigned char* init_key);

//����
void encryption();

//���ܷ�������

//���ֽ��滻
unsigned char Inv_SubBytes(unsigned char input);

//����λ��
void Inv_ShiftRows(unsigned char state_mat[][4]);

//���л��
void Inv_MixColumns(unsigned char state_mat[][4]);

//������Կ�ӣ�cnt������ǵڼ���ѭ��
void Inv_AddRoundKey(unsigned char state_mat[][4], int cnt);

//����
void decryption();


#endif