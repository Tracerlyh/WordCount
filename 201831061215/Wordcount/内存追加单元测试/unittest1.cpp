#include "stdafx.h"
#include "CppUnitTest.h"
#include"Myfun.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace 内存追加单元测试
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Wordlist a;
			a.wordlist = new Word[100];
			string b = "hello";
			a.Max = 100;
			a.NumofWord = 100;
			for (int i = 0; i < a.Max; ++i)
			{
				a.wordlist[i].spelling = "world";
			}
			a.wordlist[46].spelling = b;
			int c=CFDuplicates(b,a);
			Assert::AreEqual(46, c);
			// TODO: 在此输入测试代码
		}

	};
}