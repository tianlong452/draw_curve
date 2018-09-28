#include "Vector4.h"

//
// Default constructor
//
Vector4::Vector4() {
    set(0,0,0);
}

//
// Explicit constructor
//
Vector4::Vector4(float x, float y, float z) {
    set(x,y,z);
}

void Vector4::set(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
}

//Vector4::operator const Float4  () { return *this; } const //conversion operator
//Vector4::operator const Float4& () { return *this; } const //conversion operator

// Assignment.
Vector4& Vector4::operator=(const Float4& r) {
    copyFrom(r);
    return *this;
}

// subtract a vector from this
Vector4& Vector4::operator-=(const Vector4& r) {
    this->minus(r, *this);
    return *this;
}

// add a vector to this
Vector4& Vector4::operator+=(const Vector4& r) {
    this->plus(r, *this);
    return *this;
}

// scale this vector
Vector4& Vector4::operator*=(float amount) {
    this->times(amount, *this);
    return *this;
}

// scale this vector by reciprocal
Vector4& Vector4::operator/=(float amount) {
    assert(amount != 0);
    this->times(1.0f / amount, *this);
    return *this;
}

// Unary arithmetic operations.

// Negate (flip) this vector
Vector4 Vector4::operator-() const {
    Vector4 result;
    this->times(-1.0f, result);
    return result;
}

// Binary arithmetic operations

// Add two vectors
Vector4 Vector4::operator+(const Vector4& other) const {
    Vector4 result;
    this->plus(other, result);
    return result;
}

// subtract two vectors
Vector4 Vector4::operator-(const Vector4& other) const {
    Vector4 result;
    this->minus(other, result);
    return result;
}

// add a point: yields a point
Point4 Vector4::operator+(const Point4& other) const {
    Point4 result;
    this->plus(other, result);
    return result;
}

// Vector4-and-scalar arithmetic operations
//
// vector * scalar

Vector4 Vector4::operator*(float factor) const {
    Vector4 result;
    this->times(factor,result);
    return result;
}

//
// scalar * vector
//

Vector4 operator*(float factor, const Vector4& other) {
    return other * factor;
}

// divide (scale by reciprocal)
Vector4 Vector4::operator/(float factor) const {
    assert(factor != 0);
    Vector4 result;
    this->times(1.0f / factor, result);
    return result;
}

//
// Returns a normalized version of this vector.
//
Vector4 Vector4::normalized() const {
    Vector4 result;
    this->normalize(result);
    return result;
}

//
// Returns dot product of this and other.
// * operator is DOT product !!!!!
//
float Vector4::operator*(const Vector4& other) const {
    return dot(other);
}

//
// Returns cross product of this and other.
// ^ operator is CROSS product !!!!
//
Vector4 Vector4::operator^(const Vector4& other) const {
    Vector4 result;
    this->cross(other, result);
    return result;
}
