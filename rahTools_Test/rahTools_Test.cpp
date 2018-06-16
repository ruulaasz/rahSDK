// rahTools_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rahTools.h>
#include <iostream>
class TestClass
{
public:
	SecuredVar<int> mygetVar;
	TestClass() {};
	~TestClass() {};
};

int main()
{
	TestClass Var;
	Var.mygetVar.Set(10);
	rah::memory::Pool PoolTest;
	PoolTest.Initialize(sizeof(TestClass) * 80);
	for (int i = 0; i < 5; i++)
	{
		PoolTest.Push(&Var, sizeof(TestClass));
		Var.mygetVar.Set((1 + i)* 10);
		std::cout << Var.mygetVar.Get() << " Push to the pool " << '\n';
	}
	std::cout << "--------------------------------------------" << '\n';
	for (int i = 0; i < 6; i++)
	{
		int tmp = *((int*)PoolTest.Get(i));
		std::cout << tmp << " Get from the pool " << '\n';
	}
    return 0;
}

