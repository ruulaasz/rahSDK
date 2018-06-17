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
struct InitStruct
{
	int id;
	int size;
	float x, y, z, w;
};
struct FakeStruct
{
	int id;
};
class TestClassModule : public rah::Module<TestClassModule, InitStruct>
{
public:
	int m_id;
	int m_size;
	float m_vector[4];
	ReturnValue Initialize(InitStruct ptr)
	{
		m_id = ptr.id;
		m_size = ptr.size;
		m_vector[0] = ptr.x;
		m_vector[1] = ptr.y;
		m_vector[2] = ptr.z;
		m_vector[3] = ptr.w;
		return RAH_SUCCES;
	}
	TestClassModule() {};
	~TestClassModule() {};
};

int main()
{
	/************************************************************************/
	/* Modululo test                                                        */
	/************************************************************************/
	InitStruct newinitstruct;
	newinitstruct.id = 1;
	newinitstruct.size = 100;
	newinitstruct.x = 40;
	newinitstruct.y = 50;
	newinitstruct.z = 80;
	newinitstruct.w = 0;
	FakeStruct fakestruct;
	fakestruct.id = 1000;
	TestClassModule::StartModule(newinitstruct);
	/************************************************************************/
	/* Pool test                                                            */
	/************************************************************************/
	TestClass Var;
	Var.mygetVar.Set(10);
	rah::memory::Pool<TestClass> PoolTest;
	PoolTest.Initialize(sizeof(TestClass) * 80);
	for (int i = 0; i < 5; i++)
	{
		Var.mygetVar.Set((2 + i) * 10);
		PoolTest.Push(&Var);
		std::cout << Var.mygetVar.Get() << " Push to the pool " << '\n';
	}
	std::cout << "--------------------------------------------" << '\n';
	for (int i = 0; i < 5; i++)
	{
		TestClass* tmp = PoolTest.Get(i);
		std::cout << tmp->mygetVar.Get() << " Get from the pool " << '\n';
	}
	/************************************************************************/
	/* Delete zone                                                          */
	/************************************************************************/
	PoolTest.destroy();
	TestClassModule::CloseModule();
    return 0;
}

