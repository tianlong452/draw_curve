#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "Float4.h"
#include "Point4.h"

class Point4;

class Vector4 : public Float4 {
public:
    ////////////////////////////////////////////////////////////////
    //
    // THE METHODS YOU MUST IMPLEMENT BEGIN HERE
    //
    //*************************************************************

    //
    // Length, using three (X Y Z) components of this point.
    //
    float length() const;

    //
    // Divide first three (X Y Z) components of this point by length,
    // into result (if length==0, do nothing)
    //
    void normalize(Vector4& result) const;

    //
    // Cross product of this vector x "other", into result
    // Use only X Y Z components.
    // Sets W component of product to 0.
    //
    void cross(const Vector4& other, Vector4& result) const;

    //
    // return the angle (in radians) between this vector and "other".
    //
    float angle(Vector4& other) const;

    //*************************************************************
    //
    // THE METHODS YOU MUST IMPLEMENT END HERE
    //
    ////////////////////////////////////////////////////////////////

    //
    // Default constructor
    //
    Vector4();

    //
    // Explicit constructor
    //
    Vector4(float x, float y, float z);

    void set(float x, float y, float z);

//    operator const Float4 () const;

//    operator const Float4& () const;

    // Assignment.  Checks W component, just in case
    Vector4& operator=(const Float4& r);

    // subtract a vector from this
    Vector4& operator-=(const Vector4& r);

    // add a vector to this
    Vector4& operator+=(const Vector4& r);

    // scale this vector
    Vector4& operator*=(float amount);

    // scale this vector by reciprocal
    Vector4& operator/=(float amount);

    // Unary arithmetic operations.

    // Negate (flip) this vector
    Vector4 operator-() const;

    // Binary arithmetic operations

    // Add two vectors
    Vector4 operator+(const Vector4& other) const;

    // subtract two vectors
    Vector4 operator-(const Vector4& other) const;

    // add a point: yields a point
    Point4 operator+(const Point4& other) const;

    // Vector4-and-scalar arithmetic operations
    //
    // vector * scalar

    Vector4 operator*(float factor) const;

    //
    // scalar * vector
    //

    friend Vector4 operator*(float factor, const Vector4& other);

    // divide (scale by reciprocal)
    Vector4 operator/(float factor) const;

    //
    // Returns a normalized version of this vector.
    //
    Vector4 normalized() const;

    //
    // Returns dot product of this and other.
    // * operator is DOT product !!!!!
    //
    float operator*(const Vector4& other) const;

    //
    // Returns cross product of this and other.
    // ^ operator is CROSS product !!!!
    //
    Vector4 operator^(const Vector4& other) const;
};

#endif
