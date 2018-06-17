#pragma once
#include "rahMacros.h"
namespace rah
{
	namespace memory
	{
		/*
		* conteiner of the memory now is a template to know the size of the object
		*
		*/
		template<class T>
		class Pool
		{
		protected:
			/*
			* the total of elements in the pool
			*
			*/
			int count;
			/*
			* begin of the pool
			*
			*/
			T* poolMemory;
			/*
			* The last pointer of the pool
			*
			*/
			T* endPool;
			/*
			* The ctual position of the pool
			*
			*/
			T* actualPos;
			/*
			* The tolta size of the pool
			*
			*/
			int totalSize;
			/*
			* The remaining size
			*
			*/
			int remainingSpace;
		public:
			/*
			* Intialize the pool cosider the MemoryHeader
			*
			*/
			void Initialize(unsigned int _sizeOfPool)
			{
				poolMemory = new T[_sizeOfPool];
				totalSize = _sizeOfPool;
				remainingSpace = totalSize;
				actualPos = poolMemory;
				endPool = poolMemory + _sizeOfPool;
				count = 0;
			}
			/*
			* Push a object to the pool
			*
			*/
			void Push(T* _Object)
			{
				//checamos por si aun tenemos espacio en la pool
				if (totalSize - remainingSpace >= 0)
				{
					int rm = remainingSpace - sizeof(T);
					if (rm < 0)
						return;
					count++;//aumentamos nuestro conteo
					//escribimos la informacion del puntero
					memcpy(actualPos, _Object, sizeof(T));
					//adelantamos el puntero de actual pos
					actualPos += sizeof(T);
					remainingSpace -= sizeof(T);
				}
			}
			/*
			* Get a object in the pool
			*
			*/
			T* Get(int NInPool)
			{
				if (NInPool >= count)
					return NULL;
				T* bIterator = poolMemory + (sizeof(T) * NInPool);
				return bIterator;
			}
			/*
			* Get the remaining space in the pool
			*
			*/
			int getRemainingSpace()
			{
				return remainingSpace;
			}
			/*
			* Get the count of the pool
			*
			*/
			int getCount()
			{
				return count;
			}
			/*
			* get the size of the pool
			*
			*/
			int getSize()
			{
				return totalSize;
			}
			/*
			* Clean the elements in the pool
			*
			*/
			void clean()
			{
				RAH_ARRAY_SAFE_DELETE(poolMemory);
				Initialize(totalSize);
			}
			/*
			* Destroy the pool and its elemnts
			*
			*/
			void destroy()
			{
				RAH_ARRAY_SAFE_DELETE(poolMemory);
				poolMemory = NULL;
				totalSize = 0;
				remainingSpace = 0;
				actualPos = NULL;
				endPool = NULL;
				count = 0;
			}
		public:
			Pool()
			{
				poolMemory = NULL;
				totalSize = 0;
				remainingSpace = 0;
				actualPos = NULL;
				endPool = NULL;
				count = 0;
			}
			~Pool() {}
		};
	}
}

