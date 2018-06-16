// rahTools_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rahTools.h>

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
	int y = 0;
	y += Var.mygetVar.Get();
	int z = y;
    return 0;
}

