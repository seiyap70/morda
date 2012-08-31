/* The MIT License:

Copyright (c) 2008-2012 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

// Home page: http://morda.googlecode.com

/**
 * @author Ivan Gagis <igagis@gmail.com>
 */

#pragma once

#include <cmath> //TODO:?
#include <cstdlib> //TODO:?
#include <algorithm> //TODO:?

#ifdef DEBUG
#	include <iostream>
#endif

#include <ting/debug.hpp> //TODO:?
#include <ting/types.hpp> //TODO:?
#include <ting/math.hpp> //TODO:?
#include <ting/Exc.hpp> //TODO:?

//TODO: add throw() where needed

namespace morda{



//TODO: doxygen
template <class T> class Vector4{
public:
	//TODO: doxygen
	T x;
	
	//TODO: doxygen
	T y;
	
	//TODO: doxygen
	T z;
	
	//TODO: doxygen
	T w;

	//TODO: doxygen
	inline Vector4(){}//default constructor

	//TODO: doxygen
	inline Vector4(T x, T y, T z, T w) :
			x(x),
			y(y),
			z(z),
			w(w)
	{}

	//NOTE: copy constructor will be generated by compiler

	//TODO: doxygen
	inline Vector4(T num){
		this->operator=(num);
	}

	//TODO: doxygen
	inline Vector4(T num, T w) :
			x(num),
			y(num),
			z(num),
			w(w)
	{}

	//TODO: doxygen
	inline Vector4(const Vector2<T>& vec, T z = 0, T w = 1) :
			x(vec.x),
			y(vec.y),
			z(z),
			w(w)
	{}

	//TODO: doxygen
	inline Vector4(const Vector3<T>& vec, T w = 1) :
			x(vec.x),
			y(vec.y),
			z(vec.z),
			w(w)
	{}

	//TODO: doxygen
	inline T& operator[](unsigned i){
		ASSERT(i < 4)
		ASSERT( &((&this->x)[0]) == &this->x)
		ASSERT( &((&this->x)[1]) == &this->y)
		ASSERT( &((&this->x)[2]) == &this->z)
		ASSERT( &((&this->x)[3]) == &this->w)
		return (&this->x)[i];
	}

	//TODO: doxygen
	inline const T& operator[](unsigned i)const{
		ASSERT(i < 4)
		ASSERT( &((&this->x)[0]) == &this->x)
		ASSERT( &((&this->x)[1]) == &this->y)
		ASSERT( &((&this->x)[2]) == &this->z)
		ASSERT( &((&this->x)[3]) == &this->w)
		return (&this->x)[i];
	}

	//TODO: doxygen
	inline Vector4& operator=(const Vector4& vec){
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->w = vec.w;
		return *this;
	}

	//TODO: doxygen
	inline Vector4& operator=(const Vector3<T>& vec){
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->w = 1;
		return *this;
	}

	//TODO: doxygen
	inline Vector4& operator=(const Vector2<T>& vec){
		this->x = vec.x;
		this->y = vec.y;
		this->z = 0;
		this->w = 1;
		return *this;
	}

	//TODO: doxygen
	inline Vector4& operator=(T num){
		this->x = num;
		this->y = num;
		this->z = num;
		this->w = num;
		return (*this);
	}

	//TODO: doxygen
	inline Vector4& operator+=(const Vector2<T>& vec){
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	//TODO: doxygen
	inline Vector4& operator+=(const Vector3<T>& vec){
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

	//TODO: doxygen
	inline Vector4& operator+=(const Vector4& vec){
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		this->w += vec.w;
		return *this;
	}

	//TODO: doxygen
	inline Vector4 operator+(const Vector4& vec)const{
		return (Vector4(*this) += vec);
	}

	//TODO: doxygen
	inline Vector4& operator-=(const Vector4& vec){
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		this->w -= vec.w;
		return *this;
	}

	//TODO: doxygen
	inline Vector4 operator-(const Vector4& vec)const{
		return (Vector4(*this) -= vec);
	}

	//TODO: doxygen
	//unary minus
	inline Vector4 operator-()const{
		return Vector4(*this).Negate();
	}

	//TODO: doxygen
	inline Vector4& operator*=(T num){
		this->x *= num;
		this->y *= num;
		this->z *= num;
		this->w *= num;
		return (*this);
	}

	//TODO: doxygen
	inline Vector4 operator*(T num)const{
		return (Vector4(*this) *= num);
	}

	//TODO: doxygen
	inline friend Vector4 operator*(T num, const Vector4& vec){
		return vec * num;
	}

	//TODO: doxygen
	inline Vector4& operator/=(T num){
		ASSERT_INFO(num != 0, "Vector4::operator/=(): division by 0")
		this->x /= num;
		this->y /= num;
		this->z /= num;
		this->w /= num;
		return (*this);
	}

	//TODO: doxygen
	inline Vector4 operator/(T num){
		ASSERT_INFO(num != 0, "Vector4::operator/(): division by 0")
		return (Vector4(*this) /= num);
	}

	//TODO: doxygen
	//Dot product
	inline T operator*(const Vector4& vec)const{
		return
				this->x * vec.x +
				this->y * vec.y +
				this->z * vec.z +
				this->w * vec.w
			;
	}

	//TODO: doxygen
	//Cross product
	inline Vector4 operator%(const Vector4& vec)const{
		return Vector4(
				this->y * vec.z - this->z * vec.y,
				this->z * vec.x - this->x * vec.z,
				this->x * vec.y - this->y * vec.x,
				this->w * vec.w //TODO:???
			);
	}

	//TODO: doxygen
	inline Vector4& Negate(){
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		this->w = -this->w;
		return (*this);
	}

	//TODO: doxygen
	//power 2 of the magnitude
	inline T MagPow2()const{
		return Pow2(this->x) + Pow2(this->y) + Pow2(this->z) + Pow2(this->w);
	}

	//TODO: doxygen
	inline T Magnitude()const{
		return T(sqrt(this->MagPow2()));
	}

	//TODO: doxygen
	inline Vector4& Normalize(){
		ASSERT(this->Magnitude() != 0)
		(*this) /= this->Magnitude();
		return (*this);
	}

#ifdef DEBUG
	friend std::ostream& operator<<(std::ostream& s, const Vector4<T>& vec){
		s << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return s;
	}
#endif
};//~class Vector4



//=================================
// inline functions implementation
//=================================

//TODO:



//=====================
// Convenient typedefs
//=====================

typedef Vector4<float> Vec4f;
STATIC_ASSERT(sizeof(Vec4f) == sizeof(float) * 4)
typedef Vector4<double> Vec4d;
STATIC_ASSERT(sizeof(Vec4d) == sizeof(double) * 4)



}//~namespace