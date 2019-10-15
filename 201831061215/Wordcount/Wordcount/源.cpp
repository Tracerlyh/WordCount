#define _CRT_SECURE_NOWARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
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
			if ((num ==a.length()-1) &&((a[a.length()-1]>='!'&&a[a.length()-1]<='/') || (a[a.length() - 1] >= ':'&&a[a.length() - 1] <= '@') || (a[a.length() - 1] >= '['&&a[a.length() - 1] <= '`') || (a[a.length() - 1] >= '{'&&a[a.length() - 1] <= '`')))
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
void AdditionalMemory(Wordlist &W)//内存追加
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
void GetNumCUM(fstream &fp,Wordlist &W,string objectf)//反映文件中单词出现的频率，并将出现频率前10的单词输出到屏幕
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
		
		if (W.NumofWord >= W.Max)//内存空间已满0
		{
			AdditionalMemory(W);
		}
		fp >> word;
        if (!fp)  break;
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
	for (i = 0; i < W.NumofWord; ++i)//将前十排出来
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
	fp.close();
}
void CountChar(fstream &fp,string objectf)//统计字符数
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

	cout << "字符总数: " << numofchar << endl;
	cout << "行数:" << numofline << endl;
	fp.close();
}
void Findgoalword(Wordlist W,int n)//统计指定长度的单词的数量
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
	cout << n << "个字符长度的单词数量(不计重复单词)： " << num << endl;
	cout<<n<< "个字符长度的单词数量(计重复单词)： " << sum << endl;
}
int main()
{
	string objectf;//用来存储操作的文件的路径
	string word1;//用来存储得到的字符串
	Wordlist W;//单词表
	string longofgoalword1;//用来存储用户输入的字符串，并用来判断用户输入的是否是正整数，如果是将其转成int
	int longofgoalword=0;//用来储存用户输入的字符串转换成的整数
	int flag = 1;//交互的判断
	fstream fp1;//目标文件流
	part1:
	GetObjectFile(objectf);//提示用户输入文件路径及名字并将用户输入的文件路径存储到string类型的参数里
	fp1.open(objectf, ios::in);
	if (!fp1)
	{
		cout << "抱歉，未检测到该文件！请检查输入是否正确。    " << endl;;
		cout << "退出请输入2,"<<endl<<"重新输入文件名请输入任意数字。"<<endl;
		cout << "请输入你的命令:";
		cin >> flag;
		if (flag == 2)return 0;
		else goto part1;
	}
	cout << "正在对文件进行处理......."<<endl;
	fp1.close();
	CountChar(fp1,objectf);//统计字符数
	GetNumCUM(fp1,W,objectf);//统计单词数，统计最多的10个单词及词频
	part2:
	cout << "(扩展功能)请输入需要统计的单词长度:";
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
		cout << "  检测到非法输入!!!" << endl << "重新输入请输入1" << endl << "退出请输入任意值";
		cin >> flag;
		if (flag == 1) goto part2;
		else return 0;
	}
	for (int i = longofgoalword1.length()-1; i >=0;i--)
	{
		longofgoalword += ((int)(longofgoalword1[i] - 48))*pow(10, i);
	}
	Findgoalword(W,longofgoalword );//统计指定字符长度的单词
	system("pause");
	return 0;
}