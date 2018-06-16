#pragma once

/*Use macros or classes for any #define for general use*/

template<class t>
class SecuredVar
{
protected:
	t Var;
public:
	t Get()
	{
		return Var;
	}
	void Set(t object)
	{
		Var = object;
	}
	SecuredVar() {};
	~SecuredVar() {};
};
