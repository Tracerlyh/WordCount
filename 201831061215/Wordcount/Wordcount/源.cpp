#define _CRT_SECURE_NOWARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
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
			if ((num ==a.length()-1) &&((a[a.length()-1]>='!'&&a[a.length()-1]<='/') || (a[a.length() - 1] >= ':'&&a[a.length() - 1] <= '@') || (a[a.length() - 1] >= '['&&a[a.length() - 1] <= '`') || (a[a.length() - 1] >= '{'&&a[a.length() - 1] <= '`')))
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
void AdditionalMemory(Wordlist &W)//�ڴ�׷��
{
	Word *a;
	a = new Word[W.Max + 500];
	for (int i = 0; i < W.Max; ++i)
	{
			a[i].Soo = W.wordlist[i].Soo;
			a[i].spelling = W.wordlist[i].spelling;
	}
	delete[] W.wordlist;
	W.wordlist = new Word[W.Max + 500];
	for (int i = 0; i < W.Max + 500; ++i)
	{
		W.wordlist[i].Soo = a[i].Soo;
		W.wordlist[i].spelling = a[i].spelling;
	}
	delete[] a;
	W.Max += 500;
}
void GetNumCUM(fstream &fp,Wordlist &W,string objectf)//��ӳ�ļ��е��ʳ��ֵ�Ƶ�ʣ���������Ƶ��ǰ10�ĵ����������Ļ
{
	fp.open(objectf, ios::in);
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
			AdditionalMemory(W);
		}
		fp >> word;
        if (!fp)  break;
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
				if ((word[word.length() - 1] >= '!'&&word[word.length() - 1] <= '/') || (word[word.length() - 1] >= ':'&&word[word.length() - 1] <= '@') || (word[word.length() - 1] >= '['&&word[word.length() - 1] <= 96) || (word[word.length() - 1] >= 123 && word[word.length() - 1] <= 126))
				{
					W.wordlist[i].spelling = word.substr(0, word.length() - 1);
					W.wordlist[i].Soo++;
					W.NumofWord++;
					W.SumofWord++;
					i++;
				}
				else
				{
					W.wordlist[i].spelling = word;
					W.wordlist[i].Soo++;
					W.NumofWord++;
					W.SumofWord++;
					i++;
				}
			}
		}
	}
	int j = 0;
	int k = 0;
	for (i = 0; i < W.NumofWord; ++i)//��ǰʮ�ų���
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
			if (W.wordlist[j].Soo == W.wordlist[j + 1].Soo&&W.wordlist[j].spelling > W.wordlist[j + 1].spelling)
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
	fp.close();
}
void CountChar(fstream &fp,string objectf)//ͳ���ַ���
{
	fp.open(objectf, ios::in);
	char ch;
	double numofchar=0;
	double numofline=0;
	while(!fp.eof())
	{
		fp.get(ch);
		if ((ch >= 32 && ch <= 126)||ch=='\n')
			numofchar++;
		if (ch == '\n') numofline++;
		if (!fp)
			break;
	}
	numofchar = (numofchar >= 1) ? numofchar - 1 : numofchar;
	if (numofchar >= 1 && numofline == 0) numofline++;

	cout << "�ַ�����: " << numofchar << endl;
	cout << "����:" << numofline << endl;
	fp.close();
}
void Findgoalword(Wordlist W,int n)//ͳ��ָ�����ȵĵ��ʵ�����
{
	int num=0;
	int sum = 0;
	for (int i = 0; i < W.NumofWord; ++i)
	{
		if (W.wordlist[i].spelling.length() == n)
		{
			num++;
			sum = sum + W.wordlist[i].Soo;
		}
	}
	cout << n << "���ַ����ȵĵ�������(�����ظ�����)�� " << num << endl;
	cout<<n<< "���ַ����ȵĵ�������(���ظ�����)�� " << sum << endl;
}
int main()
{
	string objectf;//�����洢�������ļ���·��
	string word1;//�����洢�õ����ַ���
	Wordlist W;//���ʱ�
	string longofgoalword1;//�����洢�û�������ַ������������ж��û�������Ƿ���������������ǽ���ת��int
	int longofgoalword=0;//���������û�������ַ���ת���ɵ�����
	int flag = 1;//�������ж�
	fstream fp1;//Ŀ���ļ���
	part1:
	GetObjectFile(objectf);//��ʾ�û������ļ�·�������ֲ����û�������ļ�·���洢��string���͵Ĳ�����
	fp1.open(objectf, ios::in);
	if (!fp1)
	{
		cout << "��Ǹ��δ��⵽���ļ������������Ƿ���ȷ��    " << endl;;
		cout << "�˳�������2,"<<endl<<"���������ļ����������������֡�"<<endl;
		cout << "�������������:";
		cin >> flag;
		if (flag == 2)return 0;
		else goto part1;
	}
	cout << "���ڶ��ļ����д���......."<<endl;
	fp1.close();
	CountChar(fp1,objectf);//ͳ���ַ���
	GetNumCUM(fp1,W,objectf);//ͳ�Ƶ�������ͳ������10�����ʼ���Ƶ
	part2:
	cout << "(��չ����)��������Ҫͳ�Ƶĵ��ʳ���:";
	cin >> longofgoalword1;
	int j = 0;
	for (unsigned int i = 0; i < longofgoalword1.length(); ++i)
	{
		if (48 <= longofgoalword1[i] && longofgoalword1[i] <= 57)
		{
			j++;
		}
	}
	flag == 0;
	if (j != longofgoalword1.length())
	{
		cout << "  ��⵽�Ƿ�����!!!" << endl << "��������������1" << endl << "�˳�����������ֵ";
		cin >> flag;
		if (flag == 1) goto part2;
		else return 0;
	}
	for (int i = longofgoalword1.length()-1; i >=0;i--)
	{
		longofgoalword += ((int)(longofgoalword1[i] - 48))*pow(10, i);
	}
	Findgoalword(W,longofgoalword );//ͳ��ָ���ַ����ȵĵ���
	system("pause");
	return 0;
}