#pragma once

#include "rahMacros.h"
#include <string>
#include "Module.h"

namespace rah
{
	namespace debug
	{
		struct DebugInit
		{
			bool active;
			std::string filename;
			bool autosave;
			bool restOldFile = false;
		};
		class Debug : public rah::Module<rah::debug::Debug, rah::debug::DebugInit>
		{
		public:
			SecuredVar<bool> m_isActive;
			SecuredVar<bool> m_autoSave;
			SecuredVar<std::string> m_fileName;
		public:
			/*
			* Initialize the mudle for debug
			*
			*/
			RahResult Initialize(DebugInit _init);
			/*
			* Print in console a basic Log
			*
			*/
			void BasicLog(std::string _text);
			/*
			* Print in console a Log with the Line , function and file
			*
			*/
			void Log(std::string _text, int _line, char* _function, char* _file);
			/*
			* Save a basic Log in a file
			*
			*/
			void SaveBasicLog(std::string _text, std::string _filename);
			/*
			* Save a Log with the Line , function and file in a file
			*
			*/
			void SaveLog(std::string _text, std::string _filename, int _line, char* _function, char* _file);
			/*
			* Print a basic Log in the windows Output
			*
			*/
			void BasicOutputLog(std::string _text);
			/*
			* Print a Log in the windows Output
			*
			*/
			void OutputLog(std::string _text, int _line, char* _function, char* _file);
			/*
			* Empty function no had memory to delete
			*
			*/
			void Release() {}
		private:
			/*
			* Create a path if not exist
			*
			*/
			void CreatePath(std::string _filename);
			/*
			* The function to put in the output
			*
			*/
			void OutputWindow(std::string _text);
		public:
			Debug();
			~Debug();
		};
	}
}

#define RAH_DEBUGER_MODULE_DECLARATION()\
{ \
rah::debug::DebugInit tempdebuginit_; \
tempdebuginit_.active = true; \
tempdebuginit_.filename = "Log/"; \
tempdebuginit_.filename += __DATE__; \
tempdebuginit_.filename += ".txt"; \
tempdebuginit_.autosave = true; \
tempdebuginit_.restOldFile = false; \
rah::debug::Debug::StartModule(tempdebuginit_);\
}												

#define RAH_LOG(text) rah::debug::Debug::GetInstance().Log(text, __LINE__, __FUNCTION__, __FILE__)
#define RAH_BASICLOG(text) rah::debug::Debug::GetInstance().BasicLog(text)

#define RAH_SAVELOG_FILE(text, filename) rah::debug::Debug::GetInstance().SaveLog(text, filename,__LINE__, __FUNCTION__, __FILE__)
#define RAH_SAVEBASICLOG_FILE(text, filename) rah::debug::Debug::GetInstance().SaveBasicLog(text, filename)

#define RAH_SAVELOG(text) rah::debug::Debug::GetInstance().SaveLog(text, rah::debug::Debug::GetInstance().m_fileName.Get(),__LINE__, __FUNCTION__, __FILE__)
#define RAH_SAVEBASICLOG(text) rah::debug::Debug::GetInstance().SaveBasicLog(text, rah::debug::Debug::GetInstance().m_fileName.Get())

#define RAH_OUTPUTLOG(text) rah::debug::Debug::GetInstance().OutputLog(text, __LINE__, __FUNCTION__, __FILE__)
#define RAH_BASICOUTPUTLOG(text) rah::debug::Debug::GetInstance().BasicOutputLog(text)