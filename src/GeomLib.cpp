#include "GeomLib.h"

#define  PI  3.1415926
//
// Copy all components of "other" into this point.
//
void Float4::copyFrom(const Float4& other) {
	for(int i=0;i<4;++i)
		v[i] = other[i];
}

//
// Add all four components of this and "other" into sum.
//
void Float4::plus(const Float4& other, Float4& sum) const {
	for (int i = 0; i < 4; ++i)
		sum[i] = other[i] + v[i];
}

//
// Subtract all four components of "other" from this point, into difference
//
void Float4::minus(const Float4& other, Float4& difference) const {
	for (int i = 0; i < 4; ++i)
		difference[i] = v[i] - other[i];
}

//
// Dot product of all four (X Y Z W) components of "other" and this point.
//
float Float4::dot(const Float4& other) const {
	float res=0;
	for (int i = 0; i < 4; ++i)
		res += v[i] * other[i];
    return res;
}

//
// Divide all 4 of this point components by W (if W==0, do nothing),
// into result.
//
void Float4::homogenize(Float4& result) const {
	if(v[3]>EPSILON)
		for (int i = 0; i < 4; ++i)
			result[i] = v[i]/v[3];
}

//
// Multiply all four (X Y Z W) components of this point by scale factor,
// into result.
//
void Float4::times(float factor, Float4& result) const {
	for (int i = 0; i < 4; ++i)
		result[i] = v[i] * factor;
}


//
// return the distance from this point to "other".
//
float Point4::distanceTo(Point4& other) const {
	float dis = 0;
	for (int i = 0; i < 3; ++i)
		dis +=  (v[i] - other[i]) * (v[i] - other[i]);
    return sqrtf(dis);
}

//
// Length, using three (X Y Z) components of this point.
//
float Vector4::length() const {
	float len = 0;
	for (int i = 0; i < 3; ++i)
		len += v[i] * v[i];
    return sqrtf(len);
}

//
// Divide first three (X Y Z) components of this point by length,
// into result (if length==0, do nothing)
//
void Vector4::normalize(Vector4& result) const {
	float len = length();
	if(len>EPSILON)
	for (int i = 0; i < 3; ++i)
		result[i] = v[i] / len;
}

//
// Cross product of this vector x "other", into result
// Use only X Y Z components.
// Sets W component of product to 0.
//
void Vector4::cross(const Vector4& other, Vector4& result) const {
	for (int i = 0; i < 3; ++i)
		result[i] = v[(i+1)%3] * other[(i + 2) % 3] - v[(i + 2) % 3] * other[(i + 1) % 3];
	result[3] = 0;
}

//
// return the angle (in radians) between this vector and "other".
// If this or other is (0 0 0), return 0 angle.
//
float Vector4::angle(Vector4& other) const {
	if (other[0] < EPSILON && other[1] < EPSILON && other[0] < EPSILON)
		return 0;
	float rad = acos(dot(other) / length() / other.length());
    return rad;
}

//
// Copy all components of other matrix into this.
//
void Matrix4::copyFrom(const Matrix4& other) {
	for (int i = 0; i < 4; ++i)
		m[i].copyFrom(other[i]);
}

//
// Add all components of this and "other" matrix into sum
//
void Matrix4::plus(const Matrix4& other, Matrix4& sum) const {
	for (int i = 0; i < 4; ++i)
		m[i].plus(other[i],sum[i]);
}

//
// Subtract all components of this matrix minus "other", into difference
//
void Matrix4::minus(const Matrix4& other, Matrix4& difference) const {
	for (int i = 0; i < 4; ++i)
		m[i].minus(other[i], difference[i]);
}

//
// Multiply all components by factor, into product
//
void Matrix4::times(float factor, Matrix4& product) const {
	for (int i = 0; i < 4; ++i)
		m[i].times(factor,product[i]);
}

//
// Multiply (*this) x ("other"), and put product into product
//
// CAREFULL!! this may == &product!  So watch for partially-modified entries.
// Store result in temp array first!
//
void Matrix4::times(const Matrix4& other, Matrix4 &product) const {
	Matrix4 tmp;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			tmp[i][j] = 0;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				tmp[i][j] += m[i][k] * other[k][j];
	product.copyFrom(tmp);
}

//
// Multiply (*this) x ("point"), and put resulting point into "product".
// CAREFULL!! point may == product, so watch for partially-modified entries.
// Store result in temp array first!
//
void Matrix4::times(const Float4& point, Float4& product) const {
	Float4 tmp = {0,0,0,0};
	for (int i = 0; i < 4; ++i)
		for (int k = 0; k < 4; ++k)
			tmp[i] += m[i][k] * point[k];
	product.copyFrom(tmp);
}

//
// Transpose this matrix, put result into result.
//
// CAREFULL!! this may = &result!  So watch for partially-modified entries.
// Store result in temp array first!
//
void Matrix4::transpose(Matrix4& result) const {
	Matrix4 tmp;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			tmp[i][j] = m[j][i];
	result.copyFrom(tmp);
}

//
// Set this matrix to identity matrix.
//
void Matrix4::setToIdentity() {
    set(1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1);
}

//
// Set this matrix to rotation about X axis.
// "angle" is in DEGREES.
//
void Matrix4::setToXRotation(float angle) {
	float s = sinf(angle*PI/180), c = cosf(angle*PI/180);
	set(1,0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1);
}

//
// Set this matrix to rotation about Y axis.
// "angle" is in DEGREES.
//
void Matrix4::setToYRotation(float angle) {
	float s = sin(angle*PI / 180), c = cos(angle*PI / 180);
	set(c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1);
}

//
// Set this matrix to rotation about Z axis.
// "angle" is in DEGREES.
//
void Matrix4::setToZRotation(float angle) {
	float s = sinf(angle*PI / 180), c = cosf(angle*PI / 180);
	set(c, -s,0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

//
// Set this matrix to translation matrix.
//
void Matrix4::setToTranslation(float tx, float ty, float tz) {
	set(1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1);
}

//
// Set this matrix to scaling matrix.
//
void Matrix4::setToScaling(float sx, float sy, float sz) {
	set(sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
}
