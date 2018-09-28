#ifndef _FLOAT4_H_
#define _FLOAT4_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <assert.h>
#include <iostream>
#include <math.h>

#ifndef EPSILON
#define EPSILON 0.00001
#endif

using namespace std;

class Point4;

class Float4 {
public:
    ////////////////////////////////////////////////////////////////
    //
    // THE METHODS YOU MUST IMPLEMENT BEGIN HERE
    //
    //*************************************************************

    //
    // Copy all components of "other" into this point.
    //
    void copyFrom(const Float4& other);

    //
    // Add all four components of this and "other" into sum.
    //
    void plus(const Float4& other, Float4& sum) const;

    //
    // Subtract all four components of "other" from this point, into difference
    //
    void minus(const Float4& other, Float4& difference) const;

    //
    // Dot product of all four (X Y Z W) components of "other" and this point.
    //
    float dot(const Float4& other) const;

    //
    // Divide all 4 of this point components by W (if W==0, do nothing),
    // into result.
    //
    void homogenize(Float4& result) const;

    //
    // Multiply all four (X Y Z W) components of this point by scale factor,
    // into result.
    //
    void times(float factor, Float4& result) const;

    //*************************************************************
    //
    // THE METHODS YOU MUST IMPLEMENT END HERE
    //
    ////////////////////////////////////////////////////////////////

    //
    // Default constructor
    //
    Float4();

    //
    // Explicit constructor
    //
    Float4(const float x, const float y, const float z, const float w);

    //
    // Copy constructor
    //
    Float4(const Float4 &r);

    //
    // Intialize all 4 components
    //
    void set(float x, float y, float z, float w);

    Point4 homogenized();

    // Compare for equality

    bool operator==(const Float4& other);

    // Access internal components of point's data array.

    // L-value (on left of = sign)

    float& operator [](int index);

    // R-value (on right of = sign)

    const float& operator [](int index) const;

    // Named access to the four components: L-values

    float& X();
    float& Y();
    float& Z();
    float& W();

    // Named access to the components: R-values

    const float& X() const;
    const float& Y() const;
    const float& Z() const;
    const float& W() const;

    //
    // Output to stream
    //

    friend ostream& operator<<(ostream& os,const Float4& m);

    // Read from stream

    friend istream& operator>>(istream& is, Float4& p);

protected:

    // The data is stored here.

    float v[4];
};

#endif
