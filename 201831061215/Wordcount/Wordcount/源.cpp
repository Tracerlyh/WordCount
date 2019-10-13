#define _CRT_SECURE_NOWARNINGS
#include<iostream>
#include<fstream>
#include<string>
const int Maxsize=100;
using namespace std;
typedef struct
{
	string spelling;//单词的拼写（小写）
	int Soo;//单词出现次数
}Word;
typedef struct 
{
	Word *wordlist;
	int NumofWord;//词汇数(不计重复单词)
	int SumofWord;//词汇数(计重复单词)
	int Max;
}Wordlist;
void GetObjectFile(string &objectfile)//用来得到目标文件的名称或路径                                                         
{
	cout << "请输入文件名" << endl;
	cin >> objectfile;
}
bool Judgeword(string s1)//判断字符串是否为单词
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
void Togglecase(string &a)//大写转小写
{
	for (unsigned int i=0; i < a.length(); ++i)
	{

		if ('A' <= a[i]&&a[i] < 'Z')
		{
			a[i] = a[i] + 32;
		}
	}
}
int CFDuplicates(string a, Wordlist W)//查找是否有重复单词如果有返回其所在位置，如果没有返回-1
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
void Wordlistcopy(Word *a,Word *b,int MAx)//Word结构体拷贝
{
	for (int i = 0; i < MAx; ++i)
	{
		a[i].spelling = b[i].spelling;
		a[i].Soo = b[i].Soo;
	}
}
void GetNumCUM(fstream &fp)//反映文件中单词出现的频率，并将出现频率前10的单词输出到屏幕
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
		if (W.NumofWord >= W.Max)//内存空间已满0
		{
			/*Word *tf=new Word[Maxsize+20];
			Wordlistcopy(tf,W.wordlist,Maxsize);
			W.wordlist = NULL;
			W.wordlist = new Word[Maxsize + 20];
			Wordlistcopy(W.wordlist,tf,Maxsize);
			tf = NULL;
			W.Max += 20;*/
			cout << "存储空间已满"<<endl;
		}
		fp >> word;
		if (!fp)
		break;
		if (Judgeword(word))//判断是否是一个单词
		{
			Togglecase(word);
			if (CFDuplicates(word, W) != -1)//如果有重复
			{
				W.wordlist[CFDuplicates(word, W)].Soo++;//对应的单词的频率加1
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
	for (i = 0; i < 10; ++i)//将前十排出来
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
	cout << "词汇数量(不计重复单词):" << W.NumofWord<<endl;
	cout << "词汇数量(计重复单词):" << W.SumofWord << endl;
	i = 1;
	cout << "频次前十的单词：" << endl;
	while (i<=10)
	{
		if (i > W.NumofWord)
		{
			break;
		}
		else
		{
			cout <<i <<"、 "<<W.wordlist[i - 1].spelling <<" 出现频次:"<<W.wordlist[i-1].Soo<< endl;
		}
		i++;
	}
}
int main()
{
	string objectf;//用来存储操作的文件的路径
	string word1;//用来存储得到的字符串
	double Sumofchar=0;
	double Sumofword=0;
	fstream fp1;//目标文件流
	GetObjectFile(objectf);
	fp1.open(objectf, ios::in);
	cout << "正在对文件进行处理"<<endl;
	GetNumCUM(fp1);
	fp1.close();
	system("pause");
	return 0;
}