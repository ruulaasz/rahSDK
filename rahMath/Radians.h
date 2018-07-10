#pragma once

namespace rah
{
	class Degrees;

	class Radians
	{
	public:
		explicit Radians(float _value = 0.f);
		Radians(const Radians& _radians);
		Radians(const Degrees& _degrees);
		~Radians();

		void operator= (const Degrees& _degrees);
		void operator= (const Radians& _radians);

		Radians operator+ (const Degrees& _degrees);
		Radians operator+ (const Radians& _radians);

		Radians operator- (const Degrees& _degrees);
		Radians operator- (const Radians& _radians);

		void operator+= (const Degrees& _degrees);
		void operator+= (const Radians& _radians);
		
		void operator-= (const Degrees& _degrees);
		void operator-= (const Radians& _radians);

		float getDegrees();

		float m_radians;
	};
}