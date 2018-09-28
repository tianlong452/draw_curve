#include "Matrix4.h"

//
// Default constructor: set to identity matrix.
//
Matrix4::Matrix4() {
    set(1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1);
}

//
// Explicit constructor.
//

Matrix4::Matrix4(float xx, float xy, float xz, float xw,
                 float yx, float yy, float yz, float yw,
                 float zx, float zy, float zz, float zw,
                 float wx, float wy, float wz, float ww)
{
    set(xx,xy,xz,xw,
        yx,yy,yz,yw,
        zx,zy,zz,zw,
        wx,wy,wz,ww);
}

//
// Initialize all 16 components.
//

void Matrix4::set(float xx, float xy, float xz, float xw,
                  float yx, float yy, float yz, float yw,
                  float zx, float zy, float zz, float zw,
                  float wx, float wy, float wz, float ww)
{
    m[0].set(xx,xy,xz,xw);
    m[1].set(yx,yy,yz,yw);
    m[2].set(zx,zy,zz,zw);
    m[3].set(wx,wy,wz,ww);
}

//
// Copy Constructor.
//

Matrix4::Matrix4(const Matrix4& other)
{
    m[0] = other.m[0];
    m[1] = other.m[1];
    m[2] = other.m[2];
    m[3] = other.m[3];
}

//
// Set a single entry.
//
void Matrix4::set(int row, int col, float value)
{
    assert(0 <= row && row <= 3 &&
           0 <= col && col <= 3);
    m[row][col] = value;
}

//
// Array-access operators
//

Float4& Matrix4::operator[](int index)
{
    assert(0 <= index && index <= 3);
    return m[index];
}

const Float4& Matrix4::operator [](int index) const
{
    assert (0 <= index && index <= 3);
    return m[index];
}

//
// Unary operations
//

Matrix4 Matrix4::transpose() const {
    Matrix4 result;
    transpose(result);
    return result;
}

Matrix4 Matrix4::operator-() const {
    Matrix4 result;
    this->times(-1.0f, result);
    return result;
}

//
// Modifying operations.
//

Matrix4& Matrix4::operator=(const Matrix4& other) {
    copyFrom(other);
    return *this;
}

Matrix4& Matrix4::operator+=(const Matrix4& other) {
    this->plus(other, *this);
    return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& other) {
    this->minus(other, *this);
    return *this;
}

Matrix4& Matrix4::operator*=(float amount) {
    this->times(amount, *this);
    return *this;
}

Matrix4& Matrix4::operator/=(float amount) {
    assert(amount != 0);
    this->times(1.0f/amount, *this);
    return *this;
}

//
// Binary operations.
//

Matrix4 Matrix4::operator+(const Matrix4& other) const {
    Matrix4 result;
    this->plus(other, result);
    return result;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const {
    Matrix4 result;
    this->minus(other, result);
    return result;
}

Matrix4 Matrix4::operator*(float factor) const {
    Matrix4 result;
    this->times(factor, result);
    return result;
}

Matrix4 Matrix4::operator/(float factor) const {
    assert(factor != 0);
    Matrix4 result;
    this->times(1.0f/factor, result);
    return result;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    this->times(other, result);
    return result;
}

Float4 Matrix4::operator*(const Float4& other) const {
    Float4 result;
    this->times(other, result);
    return result;
}


//
// Output to a stream, in tidy format
//
ostream& operator<<(ostream& os, const Matrix4& mat) {
    os.precision(3);
    os << "["; os.width(7); os << mat[0][0];
    os << " "; os.width(7); os << mat[0][1];
    os << " "; os.width(7); os << mat[0][2];
    os << " "; os.width(7); os << mat[0][3] << "]" << endl;

    os << "|"; os.width(7); os << mat[1][0];
    os << " "; os.width(7); os << mat[1][1];
    os << " "; os.width(7); os << mat[1][2];
    os << " "; os.width(7); os << mat[1][3] << "|" << endl;

    os << "|"; os.width(7); os << mat[2][0];
    os << " "; os.width(7); os << mat[2][1];
    os << " "; os.width(7); os << mat[2][2];
    os << " "; os.width(7); os << mat[2][3] << "|" << endl;

    os << "["; os.width(7); os << mat[3][0];
    os << " "; os.width(7); os << mat[3][1];
    os << " "; os.width(7); os << mat[3][2];
    os << " "; os.width(7); os << mat[3][3] << "]" << endl;
    os.precision(6);
    return os;
}

//
// Read 16 numbers from a stream
//
istream& operator>>(istream& is, Matrix4& m) {
    for (int row=0; row<4; row++)
        for (int col=0; col<4; col++)
        {
            float val;
            is >> val;
            m[row][col] = val;
        }
    return is;
}
