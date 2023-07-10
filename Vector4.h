#pragma once
#include <math.h>
#include<stdint.h>
struct Vector4 {
	float x;
	float y;
	float z;
	float w;
};
struct Vector3 {
	float x;
	float y;
	float z;
};
struct Vector2 {
	float x;
	float y;
};
struct Matrix4x4 final {
	float m[4][4];
};
struct Transform
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};
struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};
struct Material {
	Vector4 color;
	int32_t enableLighting;
};
struct Transformmatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};
Matrix4x4 MakeRotateXMatrix(float theta);
Matrix4x4 MakeRotateYMatrix(float theta);

Matrix4x4 MakeRotateZMatrix(float theta);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);


//1　行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//２　行列の減法
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2);
//３　行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
//４　逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
//５　転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
//６　単位行列
Matrix4x4 MakeIdentity4x4();
//透視投射行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
float cot(float theta);
// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);