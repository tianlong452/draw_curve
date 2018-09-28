#include "Float4.h"
#include "Point4.h"

//
// Default constructor
//
Float4::Float4()
{
    set(0,0,0,1);
}

//
// Explicit constructor
//
Float4::Float4(const float x, const float y, const float z, const float w)
{
    set(x,y,z,w);
}

//
// Copy constructor
//
Float4::Float4(const Float4 &r)
{
    v[0] = r.v[0];
    v[1] = r.v[1];
    v[2] = r.v[2];
    v[3] = r.v[3];
}

//
// Intialize all 4 components
//
void Float4::set(float x, float y, float z, float w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

Point4 Float4::homogenized()
{
    Point4 result;
    homogenize(result);
    return result;
}

// Compare for equality

bool Float4::operator==(const Float4& other)
{
    float dx = v[0] - other[0];
    float dy = v[1] - other[1];
    float dz = v[2] - other[2];
    float dw = v[3] - other[3];

    // two points are considered equal if
    // they are close enough; exact comparisons of floats is unwise

    float sum = fabs(dx) + fabs(dy) + fabs(dz) + fabs(dw);
    return sum < EPSILON;
}

// Access internal components of point's data array.

// L-value (on left of = sign)

float& Float4::operator [](int index) {
    assert (0 <= index && index <= 3);
    return v[index];
}

// R-value (on right of = sign)

const float& Float4::operator [](int index) const {
    assert (0 <= index && index <= 3);
    return v[index];
}

// Named access to the four components: L-values

float& Float4::X() {
    return v[0];
}
float& Float4::Y() {
    return v[1];
}
float& Float4::Z() {
    return v[2];
}
float& Float4::W() {
    return v[3];
}

// Named access to the components: R-values

const float& Float4::X() const {
    return v[0];
}
const float& Float4::Y() const {
    return v[1];
}
const float& Float4::Z() const {
    return v[2];
}
const float& Float4::W() const {
    return v[3];
}

//
// Output to stream
//

ostream& operator<<(ostream& os,const Float4& m) {
    os.precision(3);
    os << "["; os.width(7); os << m.v[0];
    os << " "; os.width(7); os << m.v[1];
    os << " "; os.width(7); os << m.v[2];
    os << " "; os.width(7); os << m.v[3] << "]";
    os.precision(6);
    return os;
}

// Read from stream

istream& operator>>(istream& is, Float4& p) {
    for (int c=0;c<4;c++) {
        is >> p[c];
    }
    return is;
}

