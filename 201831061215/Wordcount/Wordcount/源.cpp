#define _CRT_SECURE_NOWARNINGS
#include<iostream>
#include<fstream>
#include<string>
const int Maxsize=100;
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
void GetObjectFile(string &objectfile)//�����õ�Ŀ���ļ������ƻ�·��                                                         
{
	cout << "�������ļ���" << endl;
	cin >> objectfile;
}
bool Judgeword(string s1)//�ж��ַ����Ƿ�Ϊ����
{
	unsigned int i;
	int j = 0;
	for (i = 0; i < s1.length(); ++i)
	{
		if (('a' <= s1[i]&&s1[i] <= 'z') ||( 'A' <= s1[i]&&s1[i] <= 'Z'))
			j++;
	}
	if (j >= 4) return true;
	else return false;
}
void Togglecase(string &a)//��дתСд
{
	for (unsigned int i=0; i < a.length(); ++i)
	{

		if ('A' <= a[i]&&a[i] < 'Z')
		{
			a[i] = a[i] + 32;
		}
	}
}
int CFDuplicates(string a, Wordlist W)//�����Ƿ����ظ���������з���������λ�ã����û�з���-1
{
	for (int i = 0; i < W.NumofWord; ++i)
	{
		if (W.wordlist[i].spelling == a)
		{
			return i;
		}
		else if(W.wordlist[i].spelling.length()==a.length()-1)
		{
			int num = 0;
			for (unsigned int j = 0; j < W.wordlist[i].spelling.length(); ++j)
			{	
				if (a[j] == W.wordlist[i].spelling[j])
					num++;
			}
			if (num == a.length() - 1 &&(a[a.length()-1]>='!'&&a[a.length()-1]<='?') )
			{
				return i;
			}
		}
	}
	return -1;
}
void Wordlistcopy(Word *a,Word *b,int MAx)//Word�ṹ�忽��
{
	for (int i = 0; i < MAx; ++i)
	{
		a[i].spelling = b[i].spelling;
		a[i].Soo = b[i].Soo;
	}
}
void GetNumCUM(fstream &fp)//��ӳ�ļ��е��ʳ��ֵ�Ƶ�ʣ���������Ƶ��ǰ10�ĵ����������Ļ
{
	Wordlist W;
	string word;
	int i = 0;
	W.wordlist = new Word[2000];
	W.NumofWord = 0;
	W.SumofWord = 0;
	W.Max = 100;
	while (!fp.eof())
	{
		if (W.NumofWord >= W.Max)//�ڴ�ռ�����0
		{
			/*Word *tf=new Word[Maxsize+20];
			Wordlistcopy(tf,W.wordlist,Maxsize);
			W.wordlist = NULL;
			W.wordlist = new Word[Maxsize + 20];
			Wordlistcopy(W.wordlist,tf,Maxsize);
			tf = NULL;
			W.Max += 20;*/
			cout << "�洢�ռ�����"<<endl;
		}
		fp >> word;
		if (!fp)
		break;
		if (Judgeword(word))//�ж��Ƿ���һ������
		{
			Togglecase(word);
			if (CFDuplicates(word, W) != -1)//������ظ�
			{
				W.wordlist[CFDuplicates(word, W)].Soo++;//��Ӧ�ĵ��ʵ�Ƶ�ʼ�1
				W.SumofWord++;
			}
			else
			{
				W.wordlist[i].Soo = 0;
				W.wordlist[i].spelling = word;
				W.wordlist[i].Soo++;
				W.NumofWord++;
				W.SumofWord++;
				i++;
			}
		}
		if (fp.eof())
			break;
	}
	int j = 0;
	int k = 0;
	for (i = 0; i < 10; ++i)//��ǰʮ�ų���
	{
		for (j = 0; j < W.NumofWord; ++j)
		{
			if (W.wordlist[j].Soo < W.wordlist[j + 1].Soo)
			{
				word = W.wordlist[j].spelling;
				k = W.wordlist[j].Soo;
				W.wordlist[j].spelling = W.wordlist[j + 1].spelling;
				W.wordlist[j].Soo = W.wordlist[j + 1].Soo;
				W.wordlist[j + 1].spelling=word;
				W.wordlist[j + 1].Soo=k;
			}
			if (W.wordlist[j].Soo == W.wordlist[j + 1].Soo&&W.wordlist[j].spelling < W.wordlist[j + 1].spelling)
			{
				word = W.wordlist[j].spelling;
				k = W.wordlist[j].Soo;
				W.wordlist[j].spelling = W.wordlist[j + 1].spelling;
				W.wordlist[j].Soo = W.wordlist[j + 1].Soo;
				W.wordlist[j + 1].spelling = word;
				W.wordlist[j + 1].Soo = k;
			}
		}
	}
	cout << "�ʻ�����(�����ظ�����):" << W.NumofWord<<endl;
	cout << "�ʻ�����(���ظ�����):" << W.SumofWord << endl;
	i = 1;
	cout << "Ƶ��ǰʮ�ĵ��ʣ�" << endl;
	while (i<=10)
	{
		if (i > W.NumofWord)
		{
			break;
		}
		else
		{
			cout <<i <<"�� "<<W.wordlist[i - 1].spelling <<" ����Ƶ��:"<<W.wordlist[i-1].Soo<< endl;
		}
		i++;
	}
}
int main()
{
	string objectf;//�����洢�������ļ���·��
	string word1;//�����洢�õ����ַ���
	double Sumofchar=0;
	double Sumofword=0;
	fstream fp1;//Ŀ���ļ���
	GetObjectFile(objectf);
	fp1.open(objectf, ios::in);
	cout << "���ڶ��ļ����д���"<<endl;
	GetNumCUM(fp1);
	fp1.close();
	system("pause");
	return 0;
}