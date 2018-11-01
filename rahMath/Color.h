#pragma once
#include "Vector4D.h"
namespace rah
{
	/**
	* A Color container class
	*
	*/
	class Color
	{
	public:
		explicit Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _alpha = 1.f);
		~Color();

		/**
		* Operator overload
		*
		*/
		void operator= (const Color& _Color);
		void operator= (const Vector4D& _vec);
		Color operator+	(const Color& _Color);
		Color operator-	(const Color& _Color);
		void operator+= (const Color& _Color);
		void operator-= (const Color& _Color);
		bool operator== (const Color& _Color);
		bool operator!= (const Color& _Color);

		/**
		* Set the values to 0.0f
		*
		*/
		void clear();

		float r;
		float g;
		float b;
		float alpha;

		static Color black;
		static Color white;
		static Color red;
		static Color green;
		static Color blue;
	};
}