#include "Point4.h"

//
// Default constructor
//
Point4::Point4() {
    set(0,0,0);
}

//
// Explicit constructor
//
Point4::Point4(const float x, const float y, const float z) {
    set(x,y,z);
}

//
// Explicit constructor
//
void Point4::set(float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
}

// Assignment.
Point4& Point4::operator=(const Float4& r) {
    copyFrom(r);
    return *this;
};

// Add a vector to this point
Point4& Point4::operator+=(const Vector4& r) {
    this->plus(r, *this);
    return *this;
}

// Binary arithmetic operations

// Sum of this point and a vector
Point4 Point4::operator+(const Vector4& other) const {
    Point4 result;
    this->plus(other, result);
    return result;
}

// Subtract a vector from this point
Point4 Point4::operator-(const Vector4& other) const {
    Point4 result;
    this->minus(other, result);
    return result;
}

// Difference of two points is a vector
Vector4 Point4::operator-(const Point4& other) const {
    Vector4 result;
    this->minus(other, result);
    return result;
}
