// rahTools_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rahTools.h>
#include <iostream>
#include <vector>
#include <vld.h>
#include <string>
#include <stdio.h>

struct TestResourceParams : public rah::BasicResourceParams
{
	int x, y;
};
class resourceTest : public rah::rahResource
{
public:
	SecuredVar<int>x;
	SecuredVar<int>y;
public:
	virtual RahResult Initialize(rah::BasicResourceParams* _params)
	{
		if (__super::Initialize(_params) != RahResult::RAH_SUCCESS)
			return RahResult::RAH_ERROR;

		TestResourceParams* params = (TestResourceParams*)_params;
		x.Set(params->x);
		y.Set(params->y);
		return Load();
	}
	virtual void Destroy()
	{
		__super::Destroy();
		x.Set(0);
		y.Set(0);
	}
	virtual RahResult Load()
	{
		return RahResult::RAH_SUCCESS;
	}
	virtual void Release()
	{

	}
	resourceTest(){}
	~resourceTest(){}
};
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
	RahResult Initialize(InitStruct ptr)
	{
		m_id = ptr.id;
		m_size = ptr.size;
		m_vector[0] = ptr.x;
		m_vector[1] = ptr.y;
		m_vector[2] = ptr.z;
		m_vector[3] = ptr.w;
		return RAH_SUCCESS;
	}
	void Release()
	{

	}
	TestClassModule() {};
	~TestClassModule() {};
};

int main()
{
	/************************************************************************/
	/* prueba de getfileName                                                */
	/************************************************************************/
	std::string filePathtest;
	filePathtest = "debug/test/tripas.obb";
	filePathtest = rah::StringUtils::GetFileNameFromPath(filePathtest);
	/************************************************************************/
	/* prueba de recurso basica                                             */
	/************************************************************************/
	rah::ResourceManagerInit tempresourcemanagerinit;
	tempresourcemanagerinit.Fabric = NULL;
	rah::ResourceManager::StartModule(tempresourcemanagerinit);
	/************************************************************************/
	/* Debug test                                                           */
	/************************************************************************/
	RAH_DEBUGER_MODULE_DECLARATION();

	RAH_LOG("Test");
	RAH_BASICLOG("Test2");

	RAH_SAVELOG_FILE("Test", "test2.txt");
	RAH_SAVEBASICLOG_FILE("Test2", "test2.txt");

	RAH_SAVELOG("Test");
	RAH_SAVEBASICLOG("Test2");

	RAH_OUTPUTLOG("Test");
	RAH_BASICOUTPUTLOG("Test2");
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
	RahResult temporlaresoult = TestClassModule::GetLastError();
	TestClassModule::StartModule(newinitstruct);
	temporlaresoult = TestClassModule::GetLastError();

	/************************************************************************/
	/* Pool test                                                            */
	/************************************************************************/
	TestClass Var;
	Var.mygetVar.Set(10);
	rah::memory::Pool<TestClass> PoolTest;
	PoolTest.Initialize(sizeof(TestClass) * 80);
	for (int i = 0; i < 80; i++)
	{
		Var.mygetVar.Set(i);
		PoolTest.Push(&Var);
		std::cout << Var.mygetVar.Get() << " Push to the pool " << '\n';
	}
	std::cout << "--------------------------------------------" << '\n';
	for (int i = 0; i < PoolTest.getCount(); i++)
	{
		TestClass* tmp = PoolTest.Get(i);
		std::cout << tmp->mygetVar.Get() << " Get from the pool " << '\n';
	}
	/************************************************************************/
	/* Prube para eliminar un std vector y los objetos dentros de ellos     */
	/************************************************************************/
	std::vector<TestClass*> vectorTest;
	for (int i = 0; i < 100; i++)
	{
		TestClass* temp = new TestClass();
		temp->mygetVar.Set(i);
		vectorTest.push_back(temp);
	}
	RAH_STDVECTOR_SAFE_DELETE(vectorTest);
	/************************************************************************/
	/* Pruebas de recursos                                                  */
	/************************************************************************/
	TestResourceParams testParams;
	testParams.filePath = "dir/here";
	testParams.id = 1;
	testParams.name = "newTest";
	testParams.x = 10;
	testParams.y = 10;
	resourceTest resourcetest;
	resourcetest.Initialize(&testParams);
	resourcetest.Destroy();
	/************************************************************************/
	/* Delete zone                                                          */
	/************************************************************************/
	PoolTest.destroy();//aqui se hace la pprueba para eliminar el array
	TestClassModule::CloseModule();
	rah::debug::Debug::CloseModule();
	rah::ResourceManager::CloseModule();
    return 0;
}

