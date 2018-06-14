// rahMath_Test.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

void printVector3(const rah::Vector3D &_vector)
{
	printf("x=%.2f, ", _vector.x);
	printf("y=%.2f, ", _vector.y);
	printf("z=%.2f", _vector.z);
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

int main()
{
	platformMathTest();

	vector3Test();

    return 0;
}