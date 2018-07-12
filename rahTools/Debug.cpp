#include "Debug.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <windows.h>
#include <sstream>

namespace rah
{
	namespace debug
	{
		RahResult Debug::Initialize(DebugInit _init)
		{
			m_isActive.Set(_init.active);
			m_fileName.Set(_init.filename);
			m_autoSave.Set(_init.autosave);
			if (_init.restOldFile)
			{
				remove(m_fileName.Get().c_str());
			}
			return RAH_SUCCESS;
		}
		void Debug::BasicLog(std::string _string)
		{
			if (m_isActive.Get())
			{
				std::cout << _string << std::endl;
			}
			if (m_autoSave.Get())
			{
				SaveBasicLog(_string, m_fileName.Get());
			}
		}
		void Debug::Log(std::string _text, int _line, char * _function, char * _file)
		{
			if (m_isActive.Get())
			{
				std::cout << "\n" << _line << "::" << _function << "::" << _file << "::" << _text << ".\n";
			}
			if (m_autoSave.Get())
			{
				SaveLog(_text, m_fileName.Get(), _line, _function, _file);
			}
		}
		void Debug::SaveBasicLog(std::string _text, std::string _filename)
		{
			if (m_isActive.Get())
			{
				FILE * pFile;
				fopen_s(&pFile, _filename.c_str(), "a");
				if (pFile == NULL)
				{
					CreatePath(_filename);
					fopen_s(&pFile, _filename.c_str(), "a");
				}
				if (pFile != NULL)
				{
					fputs(_text.c_str(), pFile);
					fputs("\n", pFile);
					fclose(pFile);
				}
			}
		}
		void Debug::SaveLog(std::string _text, std::string _filename, int _line, char * _function, char * _file)
		{
			if (m_isActive.Get())
			{
				FILE * pFile;
				fopen_s(&pFile, _filename.c_str(), "a");
				if (pFile == NULL)
				{
					CreatePath(_filename);
					fopen_s(&pFile, _filename.c_str(), "a");
				}
				if (pFile != NULL)
				{
					fputs("Line: ", pFile);
					fputs(std::to_string(_line).c_str(), pFile);
					fputs(" Function: ", pFile);
					fputs(_function, pFile);
					fputs(" File: ", pFile);
					fputs(_file, pFile);
					fputs(" Log: ", pFile);
					fputs(_text.c_str(), pFile);
					fputs("\n", pFile);
					fclose(pFile);
				}
			}
		}
		void Debug::BasicOutputLog(std::string _text)
		{
			if (m_isActive.Get())
			{
				OutputWindow(std::string("\n" + _text + "\n"));
			}
			if (m_autoSave.Get())
			{
				SaveBasicLog(_text, m_fileName.Get());
			}
		}
		void Debug::OutputLog(std::string _text, int _line, char * _function, char * _file)
		{
			if (m_isActive.Get())
			{
				OutputWindow(std::string("\nLine: " + std::to_string(_line) + " Function: " + _function + " File: " + _file + " Log: " + _text + "\n"));
			}
			if (m_autoSave.Get())
			{
				SaveLog(_text, m_fileName.Get(), _line, _function, _file);
			}
		}
		void Debug::CreatePath(std::string _filename)
		{
			std::string strPath(_filename);
			std::string strCurrent;
			int nStart, nStart1, nStart2;

			// Create the path //
			while (strPath.length())
			{
				nStart1 = (int)strPath.find('/'); if (nStart1 == std::string::npos) nStart1 = INT_MAX;
				nStart2 = (int)strPath.find('\\'); if (nStart2 == std::string::npos) nStart2 = INT_MAX;
				nStart = min(nStart1, nStart2);
				if (nStart == INT_MAX) break;
				strCurrent += strPath.substr(0, nStart) + "\\";
				strPath.erase(strPath.begin(), strPath.begin() + nStart + 1);
				CreateDirectory(strCurrent.c_str(), NULL);
			}
		}
		void Debug::OutputWindow(std::string _text)
		{
			std::wostringstream os_;
			os_ << _text.c_str();
			OutputDebugStringW(os_.str().c_str());
		}
		Debug::Debug()
		{
		}


		Debug::~Debug()
		{
		}
	}
}