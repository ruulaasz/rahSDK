// rahMath_Test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <DirectXMath.h>
#include <assert.h>

//void printVector3(const rah::Vector3D &_vector)
//{
//	printf("x=%.2f, ", _vector.x);
//	printf("y=%.2f, ", _vector.y);
//	printf("z=%.2f", _vector.z);
//}
//
//void printVector4(const rah::Vector4D &_vector)
//{
//	printf("x=%.2f, ", _vector.x);
//	printf("y=%.2f, ", _vector.y);
//	printf("z=%.2f, ", _vector.z);
//	printf("w=%.2f", _vector.w);
//}
//
//void printColor(const rah::Color &_color)
//{
//	printf("%.2f, %.2f, %.2f, %.2f", _color.r, _color.g, _color.b, _color.alpha);
//}
//
//void vector3Test()
//{
//	rah::Vector3D A;
//	rah::Vector3D B;
//
//	A.x = 1.0f;
//	A.y = 2.0f;
//	A.z = 3.0f;
//
//	B.x = 1.0f;
//	B.y = 5.0f;
//	B.z = 7.0f;
//
//	printf("~~~~VECTOR3 OPERATORS~~~");
//
//	printf("\n\nVector A: ");
//	printVector3(A);
//
//	printf("\nVector B: ");
//	printVector3(B);
//
//	rah::Vector3D C(A);
//	printf("\n\nContructor Copia Vector3D C(A)");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C = A - B;
//	printf("\n\nOperator- C=A-B");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C = A + B;
//	printf("\n\nOperator+ C=A+B");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C = A * B;
//	printf("\n\nOperator* C=A*B");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C.clear();
//	printf("\n\nFunction Clear(C)");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C += A;
//	printf("\n\nOperator+= C+=A");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C -= A;
//	printf("\n\nOperator-= C-=A");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	getchar();
//	system("cls");
//
//	printf("~~~~VECTOR3 OPERATORS PART 2~~~");
//
//	printf("\n\nVector A: ");
//	printVector3(A);
//
//	printf("\nVector B: ");
//	printVector3(B);
//
//	C = B / 2;
//	printf("\n\nOperator/ C=B/2");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C /= 2;
//	printf("\n\nOperator/= C /= 2");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	bool check = A == B;
//	printf("\n\nOperator== A == B");
//	if (check)
//		printf("\nTrue");
//	else
//		printf("\nFalse");
//
//	check = A != B;
//	printf("\n\nOperator!= A != B");
//	if (check)
//		printf("\nTrue");
//	else
//		printf("\nFalse");
//
//	C = A * 2;
//	printf("\n\nOperator* C=A*2");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C *= 2;
//	printf("\n\nOperator*= C*=2");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	printf("\n\nOperator[] C[1]");
//	printf("\n%.2f", C[1]);
//
//	getchar();
//	system("cls");
//
//	printf("~~~~VECTOR3 FUNCTIONS~~~");
//
//	printf("\n\nVector A: ");
//	printVector3(A);
//
//	printf("\nVector B: ");
//	printVector3(B);
//
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C.clear();
//	printf("\n\nFunction Clear(C)");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	float temp = A.dot(B);
//	printf("\n\nFunction Dot A.dot(B)");
//	printf("\nResult: %.2f", temp);
//
//	C = A.cross(B);
//	printf("\n\nFunction Cross A.cross(B)");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	temp = C.length();
//	printf("\n\nFunction Length C.length()");
//	printf("\nResult: %.2f", temp);
//
//	temp = C.lengthSquared();
//	printf("\n\nFunction Length C.lengthSquared()");
//	printf("\nResult: %.2f", temp);
//
//	C.escalate(2.f);
//	printf("\n\nFunction Escalate C.escalate(2.f)");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	C.truncate(1.f);
//	printf("\n\nFunction Truncate C.truncate(1.f)");
//	printf("\nVector C: ");
//	printVector3(C);
//
//	B.normalize();
//	printf("\n\nFunction Normalize B.normalize()");
//	printf("\nVector B: ");
//	printVector3(B);
//
//	getchar();
//}
//
//void platformMathTest()
//{
//	using namespace rah;
//
//	printf("~~~~MATH TRIGONOMETRIC AND CONSTANTS~~~\n\n");
//
//	float temp = math::PI;
//	printf("PI = %f", temp);
//
//	temp = 90 * math::DEG_TO_RAD;
//	printf("\n\n90 degrees to radians = %f", temp);
//
//	temp = 1.570796f * math::RAD_TO_DEG;
//	printf("\n\n1.570796 radians to degrees = %f", temp);
//
//	float radian = 90;
//	temp = math::Sin(radian);
//	printf("\n\nSin(90) radians = %f", temp);
//
//	temp = math::Cos(radian);
//	printf("\n\nCos(90) radians = %f", temp);
//
//	temp = math::Tan(radian);
//	printf("\n\nTan(90) radians = %f", temp);
//
//	radian = 0.569f;
//	temp = math::ArcSin(radian);
//	printf("\n\nArcSin(0.569) radians = %f", temp);
//
//	temp = math::ArcCos(radian);
//	printf("\n\nArcCos(0.569) radians = %f", temp);
//
//	temp = math::ArcTan(radian);
//	printf("\n\nArcTan(0.569) radians = %f", temp);
//
//	getchar();
//	system("cls");
//
//	printf("~~~~MATH OTHER OPERATIONS~~~\n\n");
//
//	radian = 6;
//	temp = math::Sqrt(radian);
//	printf("Sqrt(6) = %f", temp);
//
//	temp = math::InvSqrt(radian);
//	printf("\n\nInvSqrt(6) = %f", temp);
//
//	temp = math::Square(radian);
//	printf("\n\nSquare(6) = %f", temp);
//
//	temp = math::Pow(radian, 3);
//	printf("\n\nPow(6, 3) = %f", temp);
//
//	temp = float(math::Factorial(math::uint(radian)));
//	printf("\n\nFactorial(6) = %f", temp);
//
//	temp = math::Min(radian, 3.f);
//	printf("\n\nMin(6, 3) = %f", temp);
//
//	temp = math::Max(radian, 3.f);
//	printf("\n\nMax(6, 3) = %f", temp);
//
//	temp = math::Min3(radian, 3.f, 5.f);
//	printf("\n\nMin3(6, 3, 5) = %f", temp);
//
//	temp = math::Max3(radian, 3.f, 5.f);
//	printf("\n\nMax3(6, 3, 5) = %f", temp);
//
//	getchar();
//	system("cls");
//}
//
//void vector4Test()
//{
//	system("cls");
//	rah::Vector4D A;
//	rah::Vector4D B;
//
//	A.x = 1.0f;
//	A.y = 2.0f;
//	A.z = 3.0f;
//	A.w = 1.0f;
//
//	B.x = 1.0f;
//	B.y = 5.0f;
//	B.z = 7.0f;
//	B.w = 1.0f;
//
//	printf("~~~~VECTOR4 OPERATORS~~~");
//
//	printf("\n\nVector A: ");
//	printVector4(A);
//
//	printf("\nVector B: ");
//	printVector4(B);
//
//	rah::Vector4D C(A);
//	printf("\n\nContructor Copia Vector4D C(A)");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C = A - B;
//	printf("\n\nOperator- C=A-B");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C = A + B;
//	printf("\n\nOperator+ C=A+B");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C = A * B;
//	printf("\n\nOperator* C=A*B");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C.clear();
//	printf("\n\nFunction Clear(C)");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C += A;
//	printf("\n\nOperator+= C+=A");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C -= A;
//	printf("\n\nOperator-= C-=A");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	getchar();
//	system("cls");
//
//	printf("~~~~VECTOR4 OPERATORS PART 2~~~");
//
//	printf("\n\nVector A: ");
//	printVector4(A);
//
//	printf("\nVector B: ");
//	printVector4(B);
//
//	C = B / 2;
//	printf("\n\nOperator/ C=B/2");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C /= 2;
//	printf("\n\nOperator/= C /= 2");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	bool check = A == B;
//	printf("\n\nOperator== A == B");
//	if (check)
//		printf("\nTrue");
//	else
//		printf("\nFalse");
//
//	check = A != B;
//	printf("\n\nOperator!= A != B");
//	if (check)
//		printf("\nTrue");
//	else
//		printf("\nFalse");
//
//	C = A * 2;
//	printf("\n\nOperator* C=A*2");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C *= 2;
//	printf("\n\nOperator*= C*=2");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	printf("\n\nOperator[] C[1]");
//	printf("\n%.2f", C[1]);
//
//	getchar();
//	system("cls");
//
//	printf("~~~~VECTOR4 FUNCTIONS~~~");
//
//	printf("\n\nVector A: ");
//	printVector4(A);
//
//	printf("\nVector B: ");
//	printVector4(B);
//
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C.clear();
//	printf("\n\nFunction Clear(C)");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	float temp = A.dot(B);
//	printf("\n\nFunction Dot A.dot(B)");
//	printf("\nResult: %.2f", temp);
//
//	C = A.cross(B);
//	printf("\n\nFunction Cross A.cross(B)");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	temp = C.length();
//	printf("\n\nFunction Length C.length()");
//	printf("\nResult: %.2f", temp);
//
//	temp = C.lengthSquared();
//	printf("\n\nFunction Length C.lengthSquared()");
//	printf("\nResult: %.2f", temp);
//
//	C.escalate(2.f);
//	printf("\n\nFunction Escalate C.escalate(2.f)");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	C.truncate(1.f);
//	printf("\n\nFunction Truncate C.truncate(1.f)");
//	printf("\nVector C: ");
//	printVector4(C);
//
//	B.normalize();
//	printf("\n\nFunction Normalize B.normalize()");
//	printf("\nVector B: ");
//	printVector4(B);
//
//	getchar();
//}
//
//void colorTest()
//{
//	system("cls");
//	
//	rah::Color a;
//	a.r = 1.f;
//	a.b = 0.f;
//	a.g = 0.f;
//
//	rah::Color b;
//	b.r = 0.f;
//	b.b = 1.f;
//	b.g = 0.f;
//
//	rah::Color c;
//
//	printf("~~~~COLOR OPERATORS~~~");
//
//	printf("\n\na= ");
//	printColor(a);
//
//	printf("\nb= ");
//	printColor(b);
//
//	c = a;
//	printf("\n\nc=a\n");
//	printColor(c);
//
//	c = a + b;
//	printf("\n\nc=a+b\n");
//	printColor(c);
//
//	c = a - b;
//	printf("\n\nc=a-b\n");
//	printColor(c);
//
//	c += a;
//	printf("\n\nc+=a\n");
//	printColor(c);
//
//	c -= a;
//	printf("\n\nc-=a\n");
//	printColor(c);
//
//	bool check;
//	check = a == b;
//	printf("\n\na==b\n");
//	if (check)
//		printf("True");
//	else
//		printf("False");
//
//	check = a != b;
//	printf("\n\na!=b\n");
//	if (check)
//		printf("True");
//	else
//		printf("False");
//
//	c.clear();
//	printf("\n\nc.clear()\n");
//	printColor(c);
//
//	getchar();
//}
//
//void degreesTest()
//{
//	rah::Degrees degree(90.f);
//	rah::Degrees degreeB(45.f);
//	rah::Radians radian(degreeB);
//
//	system("cls");
//
//	printf("~~~~DEGREES OPERATORS~~~");
//
//	printf("\n\ndegree = %.2f", degree.m_degrees);
//	printf("\ndegreeB = %.2f", degreeB.m_degrees);
//	printf("\nradian = %.2f", radian.m_radians);
//
//	printf("\n\nCopy constructor");
//	rah::Degrees degreeCopy(degree);
//	printf("\ndegreeCopy = %.2f", degreeCopy.m_degrees);
//
//	printf("\n\nRadian Constructor");
//	rah::Degrees degreeRadian(radian);
//	printf("\ndegreeRadian = %.2f", degreeRadian.m_degrees);
//
//	rah::Degrees r;
//	r = degree + degreeB;
//	printf("\n\ndegree+degreeB");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r = degree + radian;
//	printf("\n\ndegree+radian");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r = degree - degreeB;
//	printf("\n\ndegree-degreeB");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r = degree - radian;
//	printf("\n\ndegree-radian");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r += degree;
//	printf("\n\nr+=degree");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r += radian;
//	printf("\n\nr+=radian");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r -= degree;
//	printf("\n\nr-=degree");
//	printf("\nr = %.2f", r.m_degrees);
//
//	r -= radian;
//	printf("\n\nr-=radian");
//	printf("\nr = %.2f", r.m_degrees);
//
//	getchar();
//}
//
//void radiansTest()
//{
//	system("cls");
//
//	printf("~~~~RADIANS OPERATORS~~~");
//
//	rah::Radians radian(1.57f);
//	rah::Radians radianB(0.785398f);
//	rah::Degrees degree(radianB);
//
//	printf("\n\nradian= %.2f", radian.m_radians);
//	printf("\nradianB = %.2f", radianB.m_radians);
//	printf("\ndegree = %.2f", degree.m_degrees);
//
//	printf("\n\nCopy constructor");
//	rah::Radians radianCopy(radian);
//	printf("\nradianCopy = %.2f", radianCopy.m_radians);
//
//	printf("\n\nDegree Constructor");
//	rah::Radians radianDegree(degree);
//	printf("\nradianDegree = %.2f", radianDegree.m_radians);
//
//	rah::Radians r;
//	r = radian + radianB;
//	printf("\n\nradian+radianB");
//	printf("\nr = %.2f", r.m_radians);
//
//	r = radian + degree;
//	printf("\n\nradian+degree");
//	printf("\nr = %.2f", r.m_radians);
//
//	r = radian - radianB;
//	printf("\n\nradian-radianB");
//	printf("\nr = %.2f", r.m_radians);
//
//	r = radian - degree;
//	printf("\n\nradian-degree");
//	printf("\nr = %.2f", r.m_radians);
//
//	r += radian;
//	printf("\n\nr+=radian");
//	printf("\nr = %.2f", r.m_radians);
//
//	r += degree;
//	printf("\n\nr+=degree");
//	printf("\nr = %.2f", r.m_radians);
//
//	r -= radian;
//	printf("\n\nr-=radian");
//	printf("\nr = %.2f", r.m_radians);
//
//	r -= degree;
//	printf("\n\nr-=degree");
//	printf("\nr = %.2f", r.m_radians);
//	
//	getchar();
//}

rah::Matrix4D XMtoRAH(const DirectX::XMMATRIX &_m)
{
	rah::Matrix4D r;

	r.m00 = _m.r[0].m128_f32[0];
	r.m01 = _m.r[0].m128_f32[1];
	r.m02 = _m.r[0].m128_f32[2];
	r.m03 = _m.r[0].m128_f32[3];

	r.m10 = _m.r[1].m128_f32[0];
	r.m11 = _m.r[1].m128_f32[1];
	r.m12 = _m.r[1].m128_f32[2];
	r.m13 = _m.r[1].m128_f32[3];

	r.m20 = _m.r[2].m128_f32[0];
	r.m21 = _m.r[2].m128_f32[1];
	r.m22 = _m.r[2].m128_f32[2];
	r.m23 = _m.r[2].m128_f32[3];

	r.m30 = _m.r[3].m128_f32[0];
	r.m31 = _m.r[3].m128_f32[1];
	r.m32 = _m.r[3].m128_f32[2];
	r.m33 = _m.r[3].m128_f32[3];

	return r;
}

void printMatrix(const rah::Matrix4D _m)
{
	printf("%.1f", _m.m00); printf(", %.1f", _m.m01); printf(", %.1f", _m.m02); printf(", %.1f", _m.m03);
	printf("\n");
	printf("%.1f", _m.m10); printf(", %.1f", _m.m11); printf(", %.1f", _m.m12); printf(", %.1f", _m.m13);
	printf("\n");
	printf("%.1f", _m.m20); printf(", %.1f", _m.m21); printf(", %.1f", _m.m22); printf(", %.1f", _m.m23);
	printf("\n");
	printf("%.1f", _m.m30); printf(", %.1f", _m.m31); printf(", %.1f", _m.m32); printf(", %.1f", _m.m33);
}

int main()
{
	/*platformMathTest();

	vector3Test();

	vector4Test();

	colorTest();

	degreesTest();

	radiansTest();*/

	DirectX::XMMATRIX DirectxMatrix;

	DirectxMatrix.r[0].m128_f32[0] = 0.52;
	DirectxMatrix.r[0].m128_f32[1] = 1.23;
	DirectxMatrix.r[0].m128_f32[2] = 0.2;
	DirectxMatrix.r[0].m128_f32[3] = 3;
	
	DirectxMatrix.r[1].m128_f32[0] = 4;
	DirectxMatrix.r[1].m128_f32[1] = 5.3;
	DirectxMatrix.r[1].m128_f32[2] = 1.25;
	DirectxMatrix.r[1].m128_f32[3] = 2;
	
	DirectxMatrix.r[2].m128_f32[0] = 8;
	DirectxMatrix.r[2].m128_f32[1] = 9;
	DirectxMatrix.r[2].m128_f32[2] = 6.699;
	DirectxMatrix.r[2].m128_f32[3] = 11;
	
	DirectxMatrix.r[3].m128_f32[0] = 12;
	DirectxMatrix.r[3].m128_f32[1] = 13;
	DirectxMatrix.r[3].m128_f32[2] = 15.26;
	DirectxMatrix.r[3].m128_f32[3] = 1.1;

	rah::Matrix4D temp = XMtoRAH(DirectxMatrix);
	printf("DirectxMatrix:\n\n");
	printMatrix(temp);

	rah::Matrix4D RahMatrix;

	RahMatrix.m00 = 0.52;
	RahMatrix.m01 = 1.23;
	RahMatrix.m02 = 0.2;
	RahMatrix.m03 = 3;
	
	RahMatrix.m10 = 4;
	RahMatrix.m11 = 5.3;
	RahMatrix.m12 = 1.25;
	RahMatrix.m13 = 2;
	
	RahMatrix.m20 = 8;
	RahMatrix.m21 = 9;
	RahMatrix.m22 = 6.699;
	RahMatrix.m23 = 11;
	
	RahMatrix.m30 = 12;
	RahMatrix.m31 = 13;
	RahMatrix.m32 = 15.26;
	RahMatrix.m33 = 1.1;

	printf("\n\nRahMatrix:\n\n");
	printMatrix(RahMatrix);

	//TRANSPOSE
	DirectX::XMMATRIX resultX = DirectX::XMMatrixTranspose(DirectxMatrix);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectxTranspose:\n\n");
	printMatrix(temp);

	rah::Matrix4D resultR = rah::math::Transpose(RahMatrix);
	printf("\n\nRahTranspose:\n\n");
	printMatrix(resultR);

	//IDENTITY
	resultX = DirectX::XMMatrixIdentity();

	temp = XMtoRAH(resultX);
	printf("\n\nDirectxIdentity:\n\n");
	printMatrix(temp);

	resultR = rah::math::Identity4D();
	printf("\n\nRahIdentity:\n\n");
	printMatrix(resultR);

	//ScalarMAtrix
	resultX = DirectX::XMMatrixScaling(5, 5, 5);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectxScalar:\n\n");
	printMatrix(temp);

	resultR = rah::math::ScalarMatrix4x4(5, 5, 5);
	printf("\n\nRahScalar:\n\n");
	printMatrix(resultR);

	//TranslationMAtrix*****
	resultX = DirectX::XMMatrixTranslation(5, 5, 5);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectxTranslation:\n\n");
	printMatrix(temp);

	resultR = rah::math::TranslationMatrix4x4(5, 5, 5);
	printf("\n\nRahTranslation:\n\n");
	printMatrix(resultR);

	//RotationX Matrix
	resultX = DirectX::XMMatrixRotationX(90);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectx RotationX:\n\n");
	printMatrix(temp);

	resultR = rah::math::RotationMatrix4x4(90, rah::math::Axis_X);
	printf("\n\nRah RotationX:\n\n");
	printMatrix(resultR);

	//RotationY Matrix
	resultX = DirectX::XMMatrixRotationY(90);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectx RotationY:\n\n");
	printMatrix(temp);

	resultR = rah::math::RotationMatrix4x4(90, rah::math::Axis_Y);
	printf("\n\nRah RotationY:\n\n");
	printMatrix(resultR);

	//RotationZ Matrix
	resultX = DirectX::XMMatrixRotationZ(90);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectx RotationZ:\n\n");
	printMatrix(temp);

	resultR = rah::math::RotationMatrix4x4(90, rah::math::Axis_Z);
	printf("\n\nRah RotationZ:\n\n");
	printMatrix(resultR);

	//Determinant Matrix
	DirectX::XMVECTOR DirectxVector = DirectX::XMMatrixDeterminant(DirectxMatrix);
	printf("\n\nDirectx Determinant:%.1f, %.1f, %.1f\n\n", DirectxVector.m128_f32[0], DirectxVector.m128_f32[1], DirectxVector.m128_f32[2]);

	float fresult = rah::math::DeterminantMatrix(RahMatrix);
	printf("Rah Determinant:%.1f", fresult);

	//Inverse Matrix
	resultX = DirectX::XMMatrixInverse(&DirectxVector, DirectxMatrix);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectx Inverse:\n\n");
	printMatrix(temp);

	resultR = rah::math::InverseMatrix4D(RahMatrix);
	printf("\n\nRah Inverse:\n\n");
	printMatrix(resultR);

	//LookAtLH Matrix
	DirectX::XMVECTOR eye;
	eye.m128_f32[0] = 0.f;
	eye.m128_f32[1] = 3.f;
	eye.m128_f32[2] = -6.f;
	eye.m128_f32[3] = 0.f;
	DirectX::XMVECTOR look;
	look.m128_f32[0] = 0.f;
	look.m128_f32[1] = 1.f;
	look.m128_f32[2] = 0.f;
	look.m128_f32[3] = 0.f;
	DirectX::XMVECTOR up;
	up.m128_f32[0] = 0.f;
	up.m128_f32[1] = 1.f;
	up.m128_f32[2] = 0.f;
	up.m128_f32[3] = 0.f;
	resultX = DirectX::XMMatrixLookAtLH(eye, look, up);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectx LookatLH:\n\n");
	printMatrix(temp);

	rah::Vector3D Eyer(0.0f, 3.0f, -6.0f);
	rah::Vector3D Atr(0.0f, 1.0f, 0.0f);
	rah::Vector3D Upr(0.0f, 1.0f, 0.0f);
	resultR = rah::math::LookAtLH(Eyer, Atr, Upr);
	printf("\n\nRah LookatLH:\n\n");
	printMatrix(resultR);

	//Perspective FOVLH Matrix
	resultX = DirectX::XMMatrixPerspectiveFovLH(rah::math::PI / 4, 640 / 480, 0.01f, 100.0f);

	temp = XMtoRAH(resultX);
	printf("\n\nDirectx PerspectoveFovLH:\n\n");
	printMatrix(temp);

	resultR = rah::math::PerspectiveFovLH(rah::math::PI / 4, 640 / 480, 0.01f, 100.0f);
	printf("\n\nRah PerspectoveFovLH:\n\n");
	printMatrix(resultR);

	getchar();

	return 0;
}