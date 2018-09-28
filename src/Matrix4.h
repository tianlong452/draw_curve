#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#ifdef WIN32
#include <windows.h>
#endif

#include <math.h>
#include <iostream>

#include "Float4.h"
#include "Point4.h"
#include "Vector4.h"

class Matrix4 {
public:
    //
    // Default constructor: set to identity matrix.
    //
    Matrix4();

    //
    // Explicit constructor.
    //

  Matrix4(float xx, float xy, float xz, float xw,
          float yx, float yy, float yz, float yw,
          float zx, float zy, float zz, float zw,
          float wx, float wy, float wz, float ww);

  //
  // Initialize all 16 components.
  //

  void set(float xx, float xy, float xz, float xw,
           float yx, float yy, float yz, float yw,
           float zx, float zy, float zz, float zw,
           float wx, float wy, float wz, float ww);

  //
  // Copy Constructor.
  //

  Matrix4(const Matrix4& other);

  //
  // Set a single entry.
  //
  void set(int row, int col, float value);

  ////////////////////////////////////////////////////////////////
  //
  // THE METHODS YOU MUST IMPLEMENT BEGIN HERE
  //
  //*************************************************************

  //
  // Copy all components of other matrix into this.
  //
  void copyFrom(const Matrix4& other);

  //
  // Add all components of this and "other" matrix into sum
  //
  void plus(const Matrix4& other, Matrix4& sum) const;

  //
  // Subtract all components of this matrix minus "other", into difference
  //
  void minus(const Matrix4& other, Matrix4& difference) const;

  //
  // Multiply all components by factor, into product
  //
  void times(float factor, Matrix4& product) const;

  //
  // Multiply (*this) x ("other"), and put product into product
  //
  // CAREFULL!! this may = &product!  So watch for partially-modified entries.
  //
  void times(const Matrix4& other, Matrix4 &product) const;

  //
  // Multiply (*this) x ("point"), and put resulting point into "product".
  //
  void times(const Float4& point, Float4& product) const;

  //
  // Transpose this matrix, put result into result.
  //
  // CAREFULL!! this may = &result!  So watch for partially-modified entries.
  //
  void transpose(Matrix4& result) const;

  //
  // Set this matrix to identity matrix.
  //
  void setToIdentity();

  //
  // Set this matrix to rotation about X axis.
  // "angle" is in DEGREES.
  //
  void setToXRotation(float angle);

  //
  // Set this matrix to rotation about Y axis.
  // "angle" is in DEGREES.
  //
  void setToYRotation(float angle);

  //
  // Set this matrix to rotation about Z axis.
  // "angle" is in DEGREES.
  //
  void setToZRotation(float angle);

  //
  // Set this matrix to translation matrix.
  //
  void setToTranslation(float tx, float ty, float tz);

  //
  // Set this matrix to scaling matrix.
  //
  void setToScaling(float sx, float sy, float sz);

  //*************************************************************
  //
  // THE METHODS YOU MUST IMPLEMENT END HERE
  //
  ////////////////////////////////////////////////////////////////

  //
  // Array-access operators
  //

  Float4& operator[](int index);

  const Float4& operator [](int index) const;

  //
  // Unary operations
  //

  Matrix4 transpose() const;

  Matrix4 operator-() const;

  //
  // Modifying operations.
  //

  Matrix4& operator=(const Matrix4& other);

  Matrix4& operator+=(const Matrix4& other);

  Matrix4& operator-=(const Matrix4& other);

  Matrix4& operator*=(float amount);

  Matrix4& operator/=(float amount);

  //
  // Binary operations.
  //

  Matrix4 operator+(const Matrix4& other) const;

  Matrix4 operator-(const Matrix4& other) const;

  Matrix4 operator*(float factor) const;

  Matrix4 operator/(float factor) const;

  Matrix4 operator*(const Matrix4& other) const;

  Float4 operator*(const Float4& other) const;

  //
  // Static matrices: standard transformations
  //

  static Matrix4 Identity() {
      Matrix4 result;
      result.setToIdentity();
      return result;
  }

  static Matrix4 XRotation(float angle) {
      Matrix4 result;
      result.setToXRotation(angle);
      return result;
  }

  static Matrix4 YRotation(float angle) {
      Matrix4 result;
      result.setToYRotation(angle);
      return result;
  }

  static Matrix4 ZRotation(float angle) {
      Matrix4 result;
      result.setToZRotation(angle);
      return result;
  }

  static Matrix4 Translation(float tx, float ty, float tz) {
      Matrix4 result;
      result.setToTranslation(tx,ty,tz);
      return result;
  }

  static Matrix4 Scaling(float sx, float sy, float sz) {
      Matrix4 result;
      result.setToScaling(sx,sy,sz);
      return result;
  }

  //
  // Output to a stream, in tidy format
  //
  friend ostream& operator<<(ostream& os, const Matrix4& mat);

  //
  // Read 16 numbers from a stream
  //
  friend istream& operator>>(istream& is, Matrix4& m);

private:
  //
  // The matrix itself.
  //
  Float4 m[4];
};

#endif
