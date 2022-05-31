﻿#pragma once

class Rational {
	int32 num;
	int32 den;

public:
	void setVal(int32 n, int32 d);

	//コンストラクタ
	Rational();
	Rational(int32 n, int32 d);
	template <std::integral T>	explicit Rational(T val);

	//getter / setter
	int32 gnum() const;
	int32 gden() const;
	void snum(int32 n);
	void sden(int32 d);

	//演算子
	//Rat .= Rat
	Rational& operator+=(const Rational& r);
	Rational& operator-=(const Rational& r);
	Rational& operator*=(const Rational& r);
	Rational& operator/=(const Rational& r);

	//Rat .= intger
	template <std::integral T> Rational& operator+=(const T& r);
	template <std::integral T> Rational& operator-=(const T& r);
	template <std::integral T> Rational& operator*=(const T& r);
	template <std::integral T> Rational& operator/=(const T& r);
	
	//型変換
	template <std::floating_point T> explicit operator T() const;
	explicit operator int32() const;
	explicit operator String() const;
};

//+=, -=, *=, /= の左辺が Rational のときに右辺に来ることができる型
template <typename T>
concept Rat_c = requires (Rational a, T b) {
	a += b;
	a -= b;
	a *= b;
	a /= b;
};

//算術演算子
//--- Rat . Rat_c
template<Rat_c T> Rational operator+(const Rational& l, const T& r);
template<Rat_c T> Rational operator-(const Rational& l, const T& r);
template<Rat_c T> Rational operator*(const Rational& l, const T& r);
template<Rat_c T> Rational operator/(const Rational& l, const T& r);
//--- integer . Rat
template<std::integral T> Rational operator+(const T& l, const Rational& r);
template<std::integral T> Rational operator-(const T& l, const Rational& r);
template<std::integral T> Rational operator*(const T& l, const Rational& r);
template<std::integral T> Rational operator/(const T& l, const Rational& r);

//比較演算子
//--- Rat . Rat_c
template<Rat_c T> bool operator< (const Rational& l, const T& r);
template<Rat_c T> bool operator> (const Rational& l, const T& r);
template<Rat_c T> bool operator<=(const Rational& l, const T& r);
template<Rat_c T> bool operator>=(const Rational& l, const T& r);
template<Rat_c T> bool operator==(const Rational& l, const T& r);
template<Rat_c T> bool operator!=(const Rational& l, const T& r);
//--- integer . Rat
template<std::integral T> bool operator< (const T& l, const Rational& r);
template<std::integral T> bool operator> (const T& l, const Rational& r);
template<std::integral T> bool operator<=(const T& l, const Rational& r);
template<std::integral T> bool operator>=(const T& l, const Rational& r);
template<std::integral T> bool operator==(const T& l, const Rational& r);
template<std::integral T> bool operator!=(const T& l, const Rational& r);

//=== Rat . flt
template<std::floating_point T> double operator+(const Rational& l, const T& r);
template<std::floating_point T> double operator-(const Rational& l, const T& r);
template<std::floating_point T> double operator*(const Rational& l, const T& r);
template<std::floating_point T> double operator/(const Rational& l, const T& r);
//=== flt . Rat
template<std::floating_point T> double operator+(const T& l, const Rational& r);
template<std::floating_point T> double operator-(const T& l, const Rational& r);
template<std::floating_point T> double operator*(const T& l, const Rational& r);
template<std::floating_point T> double operator/(const T& l, const Rational& r);

//Rational の文字列化を可能にするためのオーバーロード
//これによって Format() や Print に渡せるようになる
namespace s3d {
	void Formatter(FormatData& formatData, const Rational& r);
}

//==============================================//
//                                              //
//                     実装                     //
//                                              //
//==============================================//

void Rational::setVal(int32 n, int32 d) {
	if (d == 0) {
		throw std::runtime_error{ "denominator is Zero" };
	}
	if (d < 0) {
		d *= (-1);
		n *= (-1);
	}
	if (n == 0) {
		this->num = 0;
		this->den = 1;
		return;
	}
	int32 g = std::gcd(n, d);
	this->num = n / g;
	this->den = d / g;
}

//====================  コンストラクタ  ====================//

Rational::Rational() {
	this->num = 0;
	this->den = 1;
}

Rational::Rational(int32 n, int32 d) {
	setVal(n, d);
}

template<std::integral T>
inline Rational::Rational(T val) {
	this->num = val;
	this->den = 1;
}

//====================  getter / setter  ====================//

int32 Rational::gnum() const {
	return this->num;
}

int32 Rational::gden() const {
	return this->den;
}

void Rational::snum(int32 n) {
	setVal(n, this->den);
}

void Rational::sden(int32 d) {
	setVal(this->num, d);
}

//====================  演算子  ====================//
//=== Rat .= Rat

Rational& Rational::operator+=(const Rational& r) {
	int32 g = std::gcd(this->den, r.den);
	int32 Lrate = r.den / g;
	int32 Rrate = this->den / g;

	this->setVal(this->num * Lrate + r.num * Rrate, this->den * Lrate);
	return *this;
}

Rational& Rational::operator-=(const Rational& r) {
	*this += r * (-1);
	return *this;
}

Rational& Rational::operator*=(const Rational& r) {
	int32 glnrd = std::gcd(this->num, r.den);
	int32 gldrn = std::gcd(this->den, r.num);
	this->setVal((this->num / glnrd) * (r.num / gldrn), (this->den / gldrn) * (r.den / glnrd));
	return *this;
}

Rational& Rational::operator/=(const Rational& r) {
	*this *= Rational(r.den, r.num);
	return *this;
}

//=== Rat .= int
template<std::integral T> Rational& Rational::operator+=(const T& r) {
	*this += Rational(r);
	return *this;
}

template<std::integral T> Rational& Rational::operator-=(const T& r) {
	*this -= Rational(r);
	return *this;
}

template<std::integral T> Rational& Rational::operator*=(const T& r) {
	*this *= Rational(r);
	return *this;
}

template<std::integral T> Rational& Rational::operator/=(const T& r) {
	*this /= Rational(r);
	return *this;
}

//====================  型変換  ====================//

Rational::operator String() const { return Format(this->num, U'/', this->den); }
template<std::floating_point T> inline Rational::operator T() const { return ((T)this->num / (T)this->den); }
Rational::operator int32() const { return this->num / this->den; }

//====================  算術演算子  ====================//
//=== Rat . Rat_c
template<Rat_c T> inline Rational operator+(const Rational& l, const T& r) { return Rational(l) += r; }
template<Rat_c T> inline Rational operator-(const Rational& l, const T& r) { return Rational(l) -= r; }
template<Rat_c T> inline Rational operator*(const Rational& l, const T& r) { return Rational(l) *= r; }
template<Rat_c T> inline Rational operator/(const Rational& l, const T& r) { return Rational(l) /= r; }
//=== int . Rat
template<std::integral T> inline Rational operator+(const T& l, const Rational& r) { return Rational(l) += r; }
template<std::integral T> inline Rational operator-(const T& l, const Rational& r) { return Rational(l) -= r; }
template<std::integral T> inline Rational operator*(const T& l, const Rational& r) { return Rational(l) *= r; }
template<std::integral T> inline Rational operator/(const T& l, const Rational& r) { return Rational(l) /= r; }

//====================  比較演算子  ====================//
//=== Rat . Rat_c
template<Rat_c T> inline bool operator< (const Rational& l, const T& r) { return ((l - r).gnum() < 0); }
template<Rat_c T> inline bool operator> (const Rational& l, const T& r) { return r < l; }
template<Rat_c T> inline bool operator<=(const Rational& l, const T& r) { return !(l > r); }
template<Rat_c T> inline bool operator>=(const Rational& l, const T& r) { return !(l < r); }
template<Rat_c T> inline bool operator==(const Rational& l, const T& r) { return !(l < r) && !(l > r); }
template<Rat_c T> inline bool operator!=(const Rational& l, const T& r) { return !(l == r); }
//=== int . Rat
template<std::integral T> inline bool operator< (const T& l, const Rational& r) { return Rational(l) < r; }
template<std::integral T> inline bool operator> (const T& l, const Rational& r) { return Rational(l) > r; }
template<std::integral T> inline bool operator<=(const T& l, const Rational& r) { return Rational(l) <= r; }
template<std::integral T> inline bool operator>=(const T& l, const Rational& r) { return Rational(l) >= r; }
template<std::integral T> inline bool operator==(const T& l, const Rational& r) { return Rational(l) == r; }
template<std::integral T> inline bool operator!=(const T& l, const Rational& r) { return Rational(l) != r; }

//====================  算術演算子  ====================//
//=== Rat . flt
template<std::floating_point T> inline double operator+(const Rational& l, const T& r) { return (T)l + r; }
template<std::floating_point T> inline double operator-(const Rational& l, const T& r) { return (T)l - r; }
template<std::floating_point T> inline double operator*(const Rational& l, const T& r) { return (T)l * r; }
template<std::floating_point T> inline double operator/(const Rational& l, const T& r) { return (T)l / r; }
//=== flt . Rat
template<std::floating_point T> inline double operator+(const T& l, const Rational& r) { return l + (T)r; }
template<std::floating_point T> inline double operator-(const T& l, const Rational& r) { return l - (T)r; }
template<std::floating_point T> inline double operator*(const T& l, const Rational& r) { return l * (T)r; }
template<std::floating_point T> inline double operator/(const T& l, const Rational& r) { return l / (T)r; }

//====================  Formatter() オーバーロード  ====================//

void s3d::Formatter(FormatData& formatData, const Rational& r) { formatData.string.append((String)r); }
