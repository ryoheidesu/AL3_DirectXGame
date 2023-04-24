#include "Matrix4x4.h"
#include <cmath>

Matrix4x4 MakeScaleMatrix(const Vector3& scale) 
{	
	Matrix4x4 result;
	result = {
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

Matrix4x4 MakeRotateXMatrix(float theta) 
{
	Matrix4x4 result;
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	result = {
    1.0f,0.0f,0.0f,0.0f,
	0.0f,cos,sin,0.0f,
	0.0f,-sin,cos,0.0f,
	0.0f,0.0f,0.0f,1.0f

	};
	return result;

}

Matrix4x4 MakeRotateYMatrix(float theta) {

	Matrix4x4 result;
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	result = {
	cos,0.0f,-sin,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	sin,0.0f,cos,0.0f,
	0.0f, 0.0f, 0.0f,1.0f

	};
	return result;

}

Matrix4x4 MakeRotateZMatrix(float theta) {

	Matrix4x4 result;
	float sin = std::sin(theta);
	float cos = std::cos(theta);

	result = {
	cos,sin,0.0f,0.0f,
	-sin,cos,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f

	};
	return result;
}


Matrix4x4 MakeTranslateMatrix(const Vector3& translate) { return Matrix4x4(); }

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
	return Matrix4x4();
}

Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2) {
	// TODO: return ステートメントをここに挿入します
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix4x4(); }
