// rahMathCollisions_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rahMath.h>
#include <iostream>
int main()
{
	rah::Sphere a;
	a.m_center.Set(10, 10, 0);
	a.m_radius = 1;

	rah::Sphere b;
	b.m_center.Set(9, 10, 0);
	b.m_radius = 2;
	bool result = rah::Intersection::SphereIntersection(a, b);
	//deberia ser verdadero
	std::cout << "La esfera: " << result << "\n";

	a.m_center.Set(10, 10, 0);
	a.m_radius = 1;

	b.m_center.Set(8, 8, 0);
	b.m_radius = 1;
	result = rah::Intersection::SphereIntersection(a, b);
	//deberia ser falso
	std::cout << "La esfera: " << result << "\n";;
    return 0;
}

