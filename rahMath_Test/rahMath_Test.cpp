// rahMath_Test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

void printVector3(const rah::Vector3D &_vector)
{
	printf("x=%.2f, ", _vector.x);
	printf("y=%.2f, ", _vector.y);
	printf("z=%.2f", _vector.z);
}

void printVector4(const rah::Vector4D &_vector)
{
	printf("x=%.2f, ", _vector.x);
	printf("y=%.2f, ", _vector.y);
	printf("z=%.2f, ", _vector.z);
	printf("w=%.2f", _vector.w);
}

void printColor(const rah::Color &_color)
{
	printf("%.2f, %.2f, %.2f, %.2f", _color.r, _color.g, _color.b, _color.alpha);
}

void vector3Test()
{
	rah::Vector3D A;
	rah::Vector3D B;

	A.x = 1.0f;
	A.y = 2.0f;
	A.z = 3.0f;

	B.x = 1.0f;
	B.y = 5.0f;
	B.z = 7.0f;

	printf("~~~~VECTOR3 OPERATORS~~~");

	printf("\n\nVector A: ");
	printVector3(A);

	printf("\nVector B: ");
	printVector3(B);

	rah::Vector3D C(A);
	printf("\n\nContructor Copia Vector3D C(A)");
	printf("\nVector C: ");
	printVector3(C);

	C = A - B;
	printf("\n\nOperator- C=A-B");
	printf("\nVector C: ");
	printVector3(C);

	C = A + B;
	printf("\n\nOperator+ C=A+B");
	printf("\nVector C: ");
	printVector3(C);

	C = A * B;
	printf("\n\nOperator* C=A*B");
	printf("\nVector C: ");
	printVector3(C);

	C.clear();
	printf("\n\nFunction Clear(C)");
	printf("\nVector C: ");
	printVector3(C);

	C += A;
	printf("\n\nOperator+= C+=A");
	printf("\nVector C: ");
	printVector3(C);

	C -= A;
	printf("\n\nOperator-= C-=A");
	printf("\nVector C: ");
	printVector3(C);

	getchar();
	system("cls");

	printf("~~~~VECTOR3 OPERATORS PART 2~~~");

	printf("\n\nVector A: ");
	printVector3(A);

	printf("\nVector B: ");
	printVector3(B);

	C = B / 2;
	printf("\n\nOperator/ C=B/2");
	printf("\nVector C: ");
	printVector3(C);

	C /= 2;
	printf("\n\nOperator/= C /= 2");
	printf("\nVector C: ");
	printVector3(C);

	bool check = A == B;
	printf("\n\nOperator== A == B");
	if (check)
		printf("\nTrue");
	else
		printf("\nFalse");

	check = A != B;
	printf("\n\nOperator!= A != B");
	if (check)
		printf("\nTrue");
	else
		printf("\nFalse");

	C = A * 2;
	printf("\n\nOperator* C=A*2");
	printf("\nVector C: ");
	printVector3(C);

	C *= 2;
	printf("\n\nOperator*= C*=2");
	printf("\nVector C: ");
	printVector3(C);

	printf("\n\nOperator[] C[1]");
	printf("\n%.2f", C[1]);

	getchar();
	system("cls");

	printf("~~~~VECTOR3 FUNCTIONS~~~");

	printf("\n\nVector A: ");
	printVector3(A);

	printf("\nVector B: ");
	printVector3(B);

	printf("\nVector C: ");
	printVector3(C);

	C.clear();
	printf("\n\nFunction Clear(C)");
	printf("\nVector C: ");
	printVector3(C);

	float temp = A.dot(B);
	printf("\n\nFunction Dot A.dot(B)");
	printf("\nResult: %.2f", temp);

	C = A.cross(B);
	printf("\n\nFunction Cross A.cross(B)");
	printf("\nVector C: ");
	printVector3(C);

	temp = C.length();
	printf("\n\nFunction Length C.length()");
	printf("\nResult: %.2f", temp);

	temp = C.lengthSquared();
	printf("\n\nFunction Length C.lengthSquared()");
	printf("\nResult: %.2f", temp);

	C.escalate(2.f);
	printf("\n\nFunction Escalate C.escalate(2.f)");
	printf("\nVector C: ");
	printVector3(C);

	C.truncate(1.f);
	printf("\n\nFunction Truncate C.truncate(1.f)");
	printf("\nVector C: ");
	printVector3(C);

	B.normalize();
	printf("\n\nFunction Normalize B.normalize()");
	printf("\nVector B: ");
	printVector3(B);

	getchar();
}

void platformMathTest()
{
	using namespace rah;

	printf("~~~~MATH TRIGONOMETRIC AND CONSTANTS~~~\n\n");

	float temp = math::PI;
	printf("PI = %f", temp);

	temp = 90 * math::DEG_TO_RAD;
	printf("\n\n90 degrees to radians = %f", temp);

	temp = 1.570796f * math::RAD_TO_DEG;
	printf("\n\n1.570796 radians to degrees = %f", temp);

	float radian = 90;
	temp = math::Sin(radian);
	printf("\n\nSin(90) radians = %f", temp);

	temp = math::Cos(radian);
	printf("\n\nCos(90) radians = %f", temp);

	temp = math::Tan(radian);
	printf("\n\nTan(90) radians = %f", temp);

	radian = 0.569f;
	temp = math::ArcSin(radian);
	printf("\n\nArcSin(0.569) radians = %f", temp);

	temp = math::ArcCos(radian);
	printf("\n\nArcCos(0.569) radians = %f", temp);

	temp = math::ArcTan(radian);
	printf("\n\nArcTan(0.569) radians = %f", temp);

	getchar();
	system("cls");

	printf("~~~~MATH OTHER OPERATIONS~~~\n\n");

	radian = 6;
	temp = math::Sqrt(radian);
	printf("Sqrt(6) = %f", temp);

	temp = math::InvSqrt(radian);
	printf("\n\nInvSqrt(6) = %f", temp);

	temp = math::Square(radian);
	printf("\n\nSquare(6) = %f", temp);

	temp = math::Pow(radian, 3);
	printf("\n\nPow(6, 3) = %f", temp);

	temp = float(math::Factorial(math::uint(radian)));
	printf("\n\nFactorial(6) = %f", temp);

	temp = math::Min(radian, 3.f);
	printf("\n\nMin(6, 3) = %f", temp);

	temp = math::Max(radian, 3.f);
	printf("\n\nMax(6, 3) = %f", temp);

	temp = math::Min3(radian, 3.f, 5.f);
	printf("\n\nMin3(6, 3, 5) = %f", temp);

	temp = math::Max3(radian, 3.f, 5.f);
	printf("\n\nMax3(6, 3, 5) = %f", temp);

	getchar();
	system("cls");
}

void vector4Test()
{
	system("cls");
	rah::Vector4D A;
	rah::Vector4D B;

	A.x = 1.0f;
	A.y = 2.0f;
	A.z = 3.0f;
	A.w = 1.0f;

	B.x = 1.0f;
	B.y = 5.0f;
	B.z = 7.0f;
	B.w = 1.0f;

	printf("~~~~VECTOR4 OPERATORS~~~");

	printf("\n\nVector A: ");
	printVector4(A);

	printf("\nVector B: ");
	printVector4(B);

	rah::Vector4D C(A);
	printf("\n\nContructor Copia Vector4D C(A)");
	printf("\nVector C: ");
	printVector4(C);

	C = A - B;
	printf("\n\nOperator- C=A-B");
	printf("\nVector C: ");
	printVector4(C);

	C = A + B;
	printf("\n\nOperator+ C=A+B");
	printf("\nVector C: ");
	printVector4(C);

	C = A * B;
	printf("\n\nOperator* C=A*B");
	printf("\nVector C: ");
	printVector4(C);

	C.clear();
	printf("\n\nFunction Clear(C)");
	printf("\nVector C: ");
	printVector4(C);

	C += A;
	printf("\n\nOperator+= C+=A");
	printf("\nVector C: ");
	printVector4(C);

	C -= A;
	printf("\n\nOperator-= C-=A");
	printf("\nVector C: ");
	printVector4(C);

	getchar();
	system("cls");

	printf("~~~~VECTOR4 OPERATORS PART 2~~~");

	printf("\n\nVector A: ");
	printVector4(A);

	printf("\nVector B: ");
	printVector4(B);

	C = B / 2;
	printf("\n\nOperator/ C=B/2");
	printf("\nVector C: ");
	printVector4(C);

	C /= 2;
	printf("\n\nOperator/= C /= 2");
	printf("\nVector C: ");
	printVector4(C);

	bool check = A == B;
	printf("\n\nOperator== A == B");
	if (check)
		printf("\nTrue");
	else
		printf("\nFalse");

	check = A != B;
	printf("\n\nOperator!= A != B");
	if (check)
		printf("\nTrue");
	else
		printf("\nFalse");

	C = A * 2;
	printf("\n\nOperator* C=A*2");
	printf("\nVector C: ");
	printVector4(C);

	C *= 2;
	printf("\n\nOperator*= C*=2");
	printf("\nVector C: ");
	printVector4(C);

	printf("\n\nOperator[] C[1]");
	printf("\n%.2f", C[1]);

	getchar();
	system("cls");

	printf("~~~~VECTOR4 FUNCTIONS~~~");

	printf("\n\nVector A: ");
	printVector4(A);

	printf("\nVector B: ");
	printVector4(B);

	printf("\nVector C: ");
	printVector4(C);

	C.clear();
	printf("\n\nFunction Clear(C)");
	printf("\nVector C: ");
	printVector4(C);

	float temp = A.dot(B);
	printf("\n\nFunction Dot A.dot(B)");
	printf("\nResult: %.2f", temp);

	C = A.cross(B);
	printf("\n\nFunction Cross A.cross(B)");
	printf("\nVector C: ");
	printVector4(C);

	temp = C.length();
	printf("\n\nFunction Length C.length()");
	printf("\nResult: %.2f", temp);

	temp = C.lengthSquared();
	printf("\n\nFunction Length C.lengthSquared()");
	printf("\nResult: %.2f", temp);

	C.escalate(2.f);
	printf("\n\nFunction Escalate C.escalate(2.f)");
	printf("\nVector C: ");
	printVector4(C);

	C.truncate(1.f);
	printf("\n\nFunction Truncate C.truncate(1.f)");
	printf("\nVector C: ");
	printVector4(C);

	B.normalize();
	printf("\n\nFunction Normalize B.normalize()");
	printf("\nVector B: ");
	printVector4(B);

	getchar();
}

void colorTest()
{
	system("cls");
	
	rah::Color a;
	a.r = 1.f;
	a.b = 0.f;
	a.g = 0.f;

	rah::Color b;
	b.r = 0.f;
	b.b = 1.f;
	b.g = 0.f;

	rah::Color c;

	printf("~~~~COLOR OPERATORS~~~");

	printf("\n\na= ");
	printColor(a);

	printf("\nb= ");
	printColor(b);

	c = a;
	printf("\n\nc=a\n");
	printColor(c);

	c = a + b;
	printf("\n\nc=a+b\n");
	printColor(c);

	c = a - b;
	printf("\n\nc=a-b\n");
	printColor(c);

	c += a;
	printf("\n\nc+=a\n");
	printColor(c);

	c -= a;
	printf("\n\nc-=a\n");
	printColor(c);

	bool check;
	check = a == b;
	printf("\n\na==b\n");
	if (check)
		printf("True");
	else
		printf("False");

	check = a != b;
	printf("\n\na!=b\n");
	if (check)
		printf("True");
	else
		printf("False");

	c.clear();
	printf("\n\nc.clear()\n");
	printColor(c);

	getchar();
}

void degreesTest()
{
	rah::Degrees degree(90.f);
	rah::Degrees degreeB(45.f);
	rah::Radians radian(degreeB);

	system("cls");

	printf("~~~~DEGREES OPERATORS~~~");

	printf("\n\ndegree = %.2f", degree.m_degrees);
	printf("\ndegreeB = %.2f", degreeB.m_degrees);
	printf("\nradian = %.2f", radian.m_radians);

	printf("\n\nCopy constructor");
	rah::Degrees degreeCopy(degree);
	printf("\ndegreeCopy = %.2f", degreeCopy.m_degrees);

	printf("\n\nRadian Constructor");
	rah::Degrees degreeRadian(radian);
	printf("\ndegreeRadian = %.2f", degreeRadian.m_degrees);

	rah::Degrees r;
	r = degree + degreeB;
	printf("\n\ndegree+degreeB");
	printf("\nr = %.2f", r.m_degrees);

	r = degree + radian;
	printf("\n\ndegree+radian");
	printf("\nr = %.2f", r.m_degrees);

	r = degree - degreeB;
	printf("\n\ndegree-degreeB");
	printf("\nr = %.2f", r.m_degrees);

	r = degree - radian;
	printf("\n\ndegree-radian");
	printf("\nr = %.2f", r.m_degrees);

	r += degree;
	printf("\n\nr+=degree");
	printf("\nr = %.2f", r.m_degrees);

	r += radian;
	printf("\n\nr+=radian");
	printf("\nr = %.2f", r.m_degrees);

	r -= degree;
	printf("\n\nr-=degree");
	printf("\nr = %.2f", r.m_degrees);

	r -= radian;
	printf("\n\nr-=radian");
	printf("\nr = %.2f", r.m_degrees);

	getchar();
}

void radiansTest()
{
	system("cls");

	printf("~~~~RADIANS OPERATORS~~~");

	rah::Radians radian(1.57f);
	rah::Radians radianB(0.785398f);
	rah::Degrees degree(radianB);

	printf("\n\nradian= %.2f", radian.m_radians);
	printf("\nradianB = %.2f", radianB.m_radians);
	printf("\ndegree = %.2f", degree.m_degrees);

	printf("\n\nCopy constructor");
	rah::Radians radianCopy(radian);
	printf("\nradianCopy = %.2f", radianCopy.m_radians);

	printf("\n\nDegree Constructor");
	rah::Radians radianDegree(degree);
	printf("\nradianDegree = %.2f", radianDegree.m_radians);

	rah::Radians r;
	r = radian + radianB;
	printf("\n\nradian+radianB");
	printf("\nr = %.2f", r.m_radians);

	r = radian + degree;
	printf("\n\nradian+degree");
	printf("\nr = %.2f", r.m_radians);

	r = radian - radianB;
	printf("\n\nradian-radianB");
	printf("\nr = %.2f", r.m_radians);

	r = radian - degree;
	printf("\n\nradian-degree");
	printf("\nr = %.2f", r.m_radians);

	r += radian;
	printf("\n\nr+=radian");
	printf("\nr = %.2f", r.m_radians);

	r += degree;
	printf("\n\nr+=degree");
	printf("\nr = %.2f", r.m_radians);

	r -= radian;
	printf("\n\nr-=radian");
	printf("\nr = %.2f", r.m_radians);

	r -= degree;
	printf("\n\nr-=degree");
	printf("\nr = %.2f", r.m_radians);
	
	getchar();
}

int main()
{
	platformMathTest();

	vector3Test();

	vector4Test();

	colorTest();

	degreesTest();

	radiansTest();

    return 0;
}