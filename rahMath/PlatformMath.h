#pragma once

#include <cmath>

namespace rah
{
	namespace math
	{
		typedef unsigned int uint;
		typedef unsigned char int8;

		enum Axis
		{
			Axis_X=0, 
			Axis_Y,
			Axis_Z
		};

		/**
		* PI Constant
		*
		*/
		static const float PI = atan(1.0f) * 4;

		/**
		* Degrees to radians constant
		*
		*/
		static const float DEG_TO_RAD = PI / 180;

		/**
		* Radians to degrees constant
		*
		*/
		static const float RAD_TO_DEG = 180 / PI;

		/**
		* Returns the sin of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T Sin(T _value) { return sin(_value); };
		/**
		* Returns the sin of a float value
		* Works in radians
		*
		*/
		template<>
		static float Sin(float _value) { return sinf(_value); };

		/**
		* Returns the cos of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T Cos(T _value) { return cos(_value); };		
		/**
		* Returns the cos of a float value
		* Works in radians
		*
		*/
		template<>
		static float Cos(float _value) { return cosf(_value); };	

		/**
		* Returns the tan of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T Tan(T _value) { return tan(_value); };		
		/**
		* Returns the tan of a float value
		* Works in radians
		*
		*/
		template<>
		static float Tan(float _value) { return tanf(_value); };	

		/**
		* Returns the arcsin of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T ArcSin(T _value) { return asin(_value); };	
		/**
		* Returns the arcsin of a float value
		* Works in radians
		*
		*/
		template<>
		static float ArcSin(float _value) { return asinf(_value); };

		/**
		* Returns the arccos of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T ArcCos(T _value) { return acos(_value); };	
		/**
		* Returns the arccos of a float value
		* Works in radians
		*
		*/
		template<>
		static float ArcCos(float _value) { return acosf(_value); };

		/**
		* Returns the arctan of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T ArcTan(T _value) { return atan(_value); };	
		/**
		* Returns the arctan of a float value
		* Works in radians
		*
		*/
		template<>
		static float ArcTan(float _value) { return atanf(_value); };
	
		/**
		* Returns the squareroot of any given value
		*
		*/
		template<typename T>
		static T Sqrt(T _value) { return sqrt(_value); };
		/**
		* Returns the squareroot of a float value
		*
		*/
		template<>
		static float Sqrt(float _value)		
		{
			return sqrt(_value);			
		}

		/**
		* Returns the inverse squareroot of any given value
		*
		*/
		template<typename T>
		static T InvSqrt(T _value) { return (1 / sqrt(_value)); };
		/**
		* Returns the inverse squareroot of a float value
		*
		*/
		template<>
		static float InvSqrt(float _value) { return (1 / sqrt(_value)); };

		/**
		* Returns the square of any given value
		*
		*/
		template<typename T>
		static T Square(T _value) { return (_value*_value); };
		/**
		* Returns the square of a float value
		*
		*/
		template<>
		static float Square(float _value)							
		{
			return (_value*_value);			
		}

		/**
		* Elevates a given value to a given power
		*
		*/
		template<typename T, typename Y>
		static T Pow(T _value, Y _pow) { return pow(_value, _pow); };
		/**
		* Elevates a float value to a given power
		*
		*/
		template<>
		static float Pow(float _value, int _power) { return pow(_value, _power); };

		/**
		* Calculates the factorial of a given value
		*
		*/
		static unsigned Factorial(unsigned _value)
		{
			if (_value == 1)
				return 1;
			else
				return _value* Factorial(_value - 1);
		};

		/**
		* Returns the smallest value between 2 values
		*
		*/
		template<typename T>
		static T Min(T _value1, T _value2) { return (_value1 <= _value2 ? _value1 : _value2); };

		/**
		* Returns the bigest value between 2 values
		*
		*/
		template<typename T>
		static T Max(T _value1, T _value2) { return (_value1 >= _value2 ? _value1 : _value2); };

		/**
		* Returns the smallest value between 3 values
		*
		*/
		template<typename T>
		static T Min3(T _value1, T _value2, T _value3) { return Min(Min(_value1, _value2), _value3); };

		/**
		* Returns the bigest value between 3 values
		*
		*/
		template<typename T>
		static T Max3(T _value1, T _value2, T _value3) { return Max(Max(_value1, _value2), _value3); };
	}
}