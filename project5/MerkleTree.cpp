#include <iostream>
#include <fstream>
#include <malloc.h>
#include<vector>
#include "picosha2.h"

using namespace std;
using namespace picosha2;

int counter = 0;
int number = 2;
string leaf = "0x00";
string nleaf = "0x01";


struct node {
	string h = "";//hash
	int attr = 2;//0:leaf 1:nleaf
	node* father = NULL;
	node* left = NULL;
	node* right = NULL;
};
node root;
node* ROOT = &root;//pointer to root

/* sha256
\param      massage
\return     hash
*/
string sha(string src_str);

void update(node* p);

int upsteps(int num);

/* add node to merkle tree
\param     msg    new message to append
*/
void append(string msg);

//pre_order travasal
void preOrderTravesal(node* T);

/* Judge msg is in tree
 \param   msg         massage to judge
		  additional  is necessary for judging
		  num         0 if left,1 is right
 */
int isInMerkleTree(string msg, string additional[], int num[], int size);


int main()
{
	string tmp = "Hello";
	append(tmp);
	append("my");
	append("name");
	append("is");
	append("xxx");
	cout << "Merkle Tree ������������:\n\n";
	preOrderTravesal(ROOT);
	cout << "\n\nname �� Merkle Tree����?  "; 
	string additionForname[3] = { "6f5fd6bda530839ffa5e54681d455eb8c1ca48a9b640513ea9b38bcb3007bdae",
	"84a6106e37e642b5654b6e44fdd37cb467b7c8248c3685a244a6b6e288e39a17",
	"674f1e882584d9400ed3f39fac185419faffd6f1196651c12423acd27848fd59" };
	int numForname[3] = { 1,0,1 };
	if (isInMerkleTree("name", additionForname, numForname, 3) == 1) cout << "True\n";
	else cout << "False\n";

	return 0;
}



string sha(string src_str)
{
	string hash_hex_str;
	vector<unsigned char> hash(k_digest_size);
	hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
	hash_hex_str = bytes_to_hex_string(hash.begin(), hash.end());
	return hash_hex_str;
}



void update(node* p)
{
	while (1)
	{
		if (p == NULL)
			break;
		p->h = sha(nleaf + p->left->h + p->right->h);
		p = p->father;
	}
}

int upsteps(int num)
{
	int up = 1;
	while (1)
	{
		num = num / 2;
		if (num % 2 == 1) return up;
		else up++;
	}
}

void append(string msg)
{
	node* position = ROOT;
	if (position->left == NULL)//first
	{

		node* T = new node;
		T->attr = 0;
		T->father = ROOT;
		T->h = sha(leaf + msg);
		ROOT->left = T;
		ROOT->attr = 1;
		ROOT->h = sha(nleaf + T->h);
		counter = 1;
	}
	else if (position->right == NULL)//second
	{
		node* T = new node;
		T->attr = 0;
		T->father = ROOT;
		T->h = sha(leaf + msg);
		ROOT->right = T;
		ROOT->h = sha(nleaf + ROOT->left->h + ROOT->right->h);
		counter = 2;
	}
	else
	{
		node* T = new node;//new node with msg
		T->attr = 0;
		T->h = sha(leaf + msg);//T is node of leaf
		node* tmp = position;
		if (counter == number)
		{
			number *= 2;
			node* newroot = new node;
			newroot->attr = 1;
			newroot->h = sha(nleaf + ROOT->h + T->h);
			newroot->left = ROOT;//leftchild
			ROOT->father = newroot;//lefr's father
			newroot->right = T;//right child
			T->father = newroot;//right's father
			ROOT = newroot;//new root
		}
		else
		{
			while (1)//find the node of leaf
			{
				if (tmp->attr == 0) break;
				tmp = tmp->right;
			}
			if (counter % 2 == 0)//even
			{
				int temp = counter - (counter / 2);
				int up = upsteps(temp);
				for (int i = 0; i < up; i++) tmp = tmp->father;
			}
			node* T2 = new node;
			T2->attr = 1;
			T2->right = T;
			T->father = T2;
			T2->left = tmp;
			T2->father = tmp->father;
			tmp->father = T2;
			T2->father->right = T2;
			update(T2);
		}
		counter++;
	}
}

void preOrderTravesal(node* T)
{
	if (T == NULL)return;
	cout << T->h << endl;
	preOrderTravesal(T->left);
	preOrderTravesal(T->right);
}

int isInMerkleTree(string msg, string additional[], int num[], int size)
{
	string H = sha(leaf + msg);
	for (int i = 0; i < size; i++)
	{
		if (num[i] == 0)
			H = sha(nleaf + additional[i] + H);
		else
			H = sha(nleaf + H + additional[i]);
	}
	if (H == ROOT->h) return 1;
	else return 0;
}
