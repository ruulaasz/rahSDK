#pragma once
namespace rah
{
	namespace memory
	{
		/*
		* Struct to know the header of each object in the pool
		* Use this to create a pool considering the header
		*
		*/
		struct HeaderMemory
		{
			int size;
			int NumberInPool;
		};
		/*
		* conteiner of the memory
		*
		*/
		class Pool
		{
		protected:
			/*
			* the total of elements in the pool
			*
			*/
			int count;
			/*
			* the pool
			*
			*/
			void* poolMemory;
			/*
			* Begin of the pool memory
			*
			*/
			void* beginPos;
			/*
			* The last pointer of the pool
			*
			*/
			void* lastPos;
			/*
			* The ctual position of the pool
			*
			*/
			void* actualPos;
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
			void Initialize(unsigned int _sizeOfPool);
			/*
			* Push a object to the pool
			*
			*/
			void Push(void* _Object, int size);
			/*
			* Get a object in the pool
			*
			*/
			void* Get(int NInPool);
			/*
			* Get the remaining space in the pool
			*
			*/
			int getRemainingSpace();
			/*
			* Get the count of the pool
			*
			*/
			int getCount();
			/*
			* get the size of the pool
			*
			*/
			int getSize();
			/*
			* Clean the elements in the pool
			*
			*/
			void clean();
			/*
			* Destroy the pool and its elemnts
			*
			*/
			void destroy();
		public:
			Pool();
			~Pool();
		};
	}
}

