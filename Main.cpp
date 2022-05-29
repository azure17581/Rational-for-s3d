#include <Siv3D.hpp> // OpenSiv3D v0.6.3
#include "rational.h"

void Main() {
	//Rational(分子, 分母) の形で初期化
	Rational r1(3, 5), r2(7, 6), r3(-3, 7), r4(3, 4);
	Print << r1 << U" + " << r4 << U" = " << (r1 + r4);
	Print << r4 << U" - " << r2 << U" = " << (r4 - r2);
	Print << r3 << U" * " << r1 << U" = " << (r3 * r1);
	Print << r2 << U" ÷ " << r1 << U" = " << (r2 / r1);

	//int からの構築も可
	Print << Rational(3);

	//Rational と 整数 の演算は Rational
	Print << r2 << U" + " << 2 << U" = " << (r2 + 2);

	//Rational と 浮動小数 の演算は float
	Print << r3 << U" + " << 4.6 << U" = " << (r3 + 4.6);

	while (System::Update()) {
	}
}