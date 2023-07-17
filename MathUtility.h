#pragma once

#include "Vector3.h"
#include "Matrix4x4.h"
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Vector3 Transform(Vector3 vector, Matrix4x4 matrix);
