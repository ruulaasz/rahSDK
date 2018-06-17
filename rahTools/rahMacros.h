#pragma once

/*Use macros or classes for any #define for general use*/
/*
* Generic valor of returning functions
*
*/
enum ReturnValue
{
	RAH_SUCCES = 0,
	RAH_ERROR
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
