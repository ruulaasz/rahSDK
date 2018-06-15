#pragma once

namespace rah
{
	class Radians;

	class Degrees
	{
	public:
		explicit Degrees(float _value = 0.f);
		Degrees(const Degrees& _degrees);
		Degrees(const Radians& _radians);
		virtual ~Degrees();

		void operator= (const Degrees& _degrees);
		void operator= (const Radians& _radians);

		Degrees operator+ (const Degrees& _degrees);
		Degrees operator+ (const Radians& _radians);

		Degrees operator- (const Degrees& _degrees);
		Degrees operator- (const Radians& _radians);

		void operator+= (const Degrees& _degrees);
		void operator+= (const Radians& _radians);

		void operator-= (const Degrees& _degrees);
		void operator-= (const Radians& _radians);

		float getRadians();

		float m_degrees;
	};
}