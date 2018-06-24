#pragma once

/*Use macros or classes for any #define for general use*/

/************************************************************************/
/* Safe Deletes                                                         */
/************************************************************************/
#define RAH_SAFE_DELETE(ptr) if(ptr != NULL) delete ptr; ptr=NULL;
#define RAH_ARRAY_SAFE_DELETE(ptr) if(ptr != NULL) delete[] ptr; ptr=NULL;
#define RAH_STDVECTOR_SAFE_DELETE(ptr) while(!ptr.empty()){ RAH_SAFE_DELETE(ptr.back()); ptr.pop_back();}
/*
* Generic valor of returning functions
*
*/
enum RahResult
{
	RAH_ERROR = -1,
	RAH_SUCCESS = 0
};
template<class t>
/*
* A generic set get container
*
*/
class SecuredVar
{
protected:
	/*
	* Protecter var
	*
	*/
	t Var;
public:
	/*
	* Get fuction to get the protected var
	*
	*/
	t Get()
	{
		return Var;
	}
	/*
	* Set function to set a new value to the var
	*
	*/
	void Set(t object)
	{
		Var = object;
	}
	t operator=(t _other)
	{
		Var = _other;
	}
	/*
	* Empty constructor
	*
	*/
	SecuredVar() {};
	/*
	* Empty destructor
	*
	*/
	~SecuredVar() {};
};
