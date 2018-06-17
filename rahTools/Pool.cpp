#include "Pool.h"
#include <tchar.h>

namespace rah
{
	namespace memory
	{
		void Pool::Initialize(unsigned int _sizeOfPool)
		{
			poolMemory = new char(_sizeOfPool);
			totalSize = _sizeOfPool;
			remainingSpace = totalSize;
			beginPos = poolMemory;
			actualPos = poolMemory;
			lastPos = &poolMemory + _sizeOfPool;
			count = 0;
		}

		void Pool::Push(void * _Object, int size)
		{
			//checamos por si aun tenemos espacio en la pool
			if (totalSize - remainingSpace >= 0)
			{
				int rm = remainingSpace - (size + sizeof(HeaderMemory));
				if (rm < 0)
					return;
				//Creamos nuestro encabezado
				HeaderMemory *MH = new HeaderMemory();
				MH->NumberInPool = count;
				MH->size = size;
				count++;//aumentamos nuestro conteo
						//copiamos la memoria del encabezado
				memcpy(actualPos, MH, sizeof(HeaderMemory));
				char * cp = reinterpret_cast<char*>(actualPos);
				cp += sizeof(HeaderMemory);//movemos el puntero
				actualPos = (void*)cp;
				//escribimos la informacion del puntero
				memcpy(actualPos, _Object, size);
				cp = reinterpret_cast<char*>(actualPos);
				cp += size;
				actualPos = (void*)cp;
				remainingSpace -= size + sizeof(HeaderMemory);
			}
		}

		void * Pool::Get(int NInPool)
		{
			if (NInPool >= count)
				return nullptr;
			void* ptr = beginPos;
			HeaderMemory MH;
			for (int i = 0; i < count; i++)
			{
				memcpy(&MH, ptr, sizeof(HeaderMemory));
				char* cp = reinterpret_cast<char*>(ptr);
				if (MH.NumberInPool == NInPool)
				{
					cp += sizeof(HeaderMemory);
					char* rrnValue;
					memcpy(&rrnValue, cp, MH.size);
					return rrnValue;
				}
				cp += MH.size + sizeof(HeaderMemory);
				ptr = (void*)cp;
			}
			return nullptr;
		}

		int Pool::getRemainingSpace()
		{
			return remainingSpace;
		}

		int Pool::getCount()
		{
			return count;
		}

		int Pool::getSize()
		{
			return totalSize;
		}

		void Pool::clean()
		{
			delete[] poolMemory;
			Initialize(totalSize);
		}

		void Pool::destroy()
		{
			delete[] poolMemory;
			poolMemory = NULL;
			totalSize = 0;
			remainingSpace = 0;
			beginPos = NULL;
			actualPos = NULL;
			lastPos = NULL;
			count = 0;
		}

		Pool::Pool()
		{
		}


		Pool::~Pool()
		{
		}
	}
}