#ifndef _POINT4_H_
#define _POINT4_H_

#include "Float4.h"
#include "Vector4.h"

class Vector4;

class Point4 : public Float4 {
public:
    ////////////////////////////////////////////////////////////////
    //
    // THE METHODS YOU MUST IMPLEMENT BEGIN HERE
    //
    //*************************************************************

    //
    // return the distance from this point to "other".
    //
    float distanceTo(Point4& other) const;

    //*************************************************************
    //
    // THE METHODS YOU MUST IMPLEMENT END HERE
    //
    ////////////////////////////////////////////////////////////////

    //
    // Default constructor
    //
    Point4();

    //
    // Explicit constructor
    //
    Point4(const float x, const float y, const float z);

    //
    // Change the values
    //
    void set(float x, float y, float z);

    // Assignment.  Checks W component, just in case
    Point4& operator=(const Float4& r);

    // Add a vector to this point
    Point4& operator+=(const Vector4& r);

    // Binary arithmetic operations

    // Sum of this point and a vector
    Point4 operator+(const Vector4& other) const;

    // Subtract a vector from this point
    Point4 operator-(const Vector4& other) const;

    // Difference of two points is a vector
    Vector4 operator-(const Point4& other) const;
};

#endif
