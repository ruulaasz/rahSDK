#pragma once
namespace rah
{
	/************************************************************************/
	/* Foward Declaration                                                   */
	/************************************************************************/
	class Matrix4D;
	class Vector4D;
	class Radians;
	/************************************************************************/
	/* Delcaracion de enumeradores utiles para la clase KJQuaternion        */
	/************************************************************************/
	enum rahOrderAxis
	{
		XYZ = 0, XZY,
		YZX, YXZ,
		ZXY, ZYX
	};
	/************************************************************************/
	/* Declaracion de la clase KJQuaternion                                 */
	/************************************************************************/
	class Quaternion
	{
	public:
		/************************************************************************/
		/* Declaracion de contructores y destructor                             */
		/************************************************************************/
		explicit Quaternion(float _x = 0, float _y = 0, float _z = 0, float _w = 0) :X(_x), Y(_y), Z(_z), W(_w) {};
		Quaternion(Vector4D _vector);
		~Quaternion();

	public:
		/************************************************************************/
		/* Declaracion de variables miembro de la clase                         */
		/************************************************************************/
		float X;
		float Y;
		float Z;
		float W;

		static const Quaternion Indentity;

	public:
		/************************************************************************/
		/* Declaracion de funciones de la clase                                 */
		/************************************************************************/
		float DotProduct(Quaternion _SecondQuaterion);
		float Magnitude();
		Quaternion Normalize();
		Quaternion Inverse();
		Quaternion Slerp(const Quaternion _SecondQuaterion, float _time);
		Matrix4D QuaternionToMatrix4D();
		Quaternion Matrix4DToQuaternion(const Matrix4D _Matrix);
		Quaternion EulerToQuaternion(Radians& _Headding, Radians& _Attitude, Radians& _Bank);
		//INVERSO

	public:
		/************************************************************************/
		/* Sobrecarga de operadores                                             */
		/************************************************************************/
		//operadores aritmeticos
		Quaternion operator=(Vector4D _vector);
		Quaternion operator=(Matrix4D _Matrix);
		Quaternion operator+(Quaternion _Quaternion);
		Quaternion operator-(Quaternion _Quaternion);
		Quaternion operator*(Quaternion _Quaternion);
		Quaternion operator/(Quaternion _Quaternion);
		Quaternion operator/(float _valor);
		//operadores de condicion
		bool operator==(Quaternion _Quaternion);
		bool operator!=(Quaternion _Quaternion);
		bool operator>(Quaternion _Quaternion);
		bool operator>=(Quaternion _Quaternion);
		bool operator<(Quaternion _Quaternion);
		bool operator<=(Quaternion _Quaternion);

	};
}

