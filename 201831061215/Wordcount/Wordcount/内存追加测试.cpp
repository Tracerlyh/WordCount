#define _CRT_SECURE_NOWARNINGS
#include<iostream>
#include<fstream>
#include<string>
const int Maxsize = 100;
using namespace std;
typedef struct
{
	string spelling;//���ʵ�ƴд��Сд��
	int Soo;//���ʳ��ִ���
}Word;
typedef struct
{
	Word *wordlist;
	int NumofWord;//�ʻ���(�����ظ�����)
	int SumofWord;//�ʻ���(���ظ�����)
	int Max;
}Wordlist;
int main()
{
	Wordlist W;
	W.wordlist = new Word[10];
	W.Max = 10;
	for (int i = 0; i < W.Max; ++i)
	{
		W.wordlist[i].spelling = "myname";
		W.wordlist[i].Soo = 1;
	}
	Word *a;
	a = new Word[W.Max + 5];
	for (int i = 0; i < W.Max+5; ++i)
	{
		if (i < W.Max)
		{
			a[i].Soo = W.wordlist[i].Soo;
			a[i].spelling = W.wordlist[i].spelling;
		}
		/*else
		{
			a[i].spelling = "yourname";
			a[i].Soo = 2;
		}*/
	}
	delete[] W.wordlist;
	W.wordlist = new Word[W.Max + 5];
	for (int i = 0; i < W.Max + 5; ++i)
	{
			W.wordlist[i].Soo=a[i].Soo;
			W.wordlist[i].spelling = a[i].spelling;
	}
	delete[] a;
	W.Max += 5;
	for (int i = 0; i < W.Max; ++i)
	{
		cout << W.wordlist[i].spelling << endl;
		cout << W.wordlist[i].Soo << endl;
	}
	system("pause");
	return 0;
}