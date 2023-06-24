#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
#include "base/MyEngine.h"
class Sphere
{
public:
	void Initialize(DirectXCommon* dxCommon, MyEngine* engine);


	void Draw(const Vector4& material, const Matrix4x4& wvpdata);
	void Finalize();
private:
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	ID3D12Resource* vertexResource;
	VertexData* vertexData_;
	//ID3D12Resource* transformationMatrixResource;
	//Matrix4x4* transformationMatrixdata;
	ID3D12Resource* wvpResource_;
	Matrix4x4* wvpData_;
	ID3D12Resource* materialResource_;
	Vector4* materialData_;
	MyEngine* engine_;
	const float pi = 3.1415f;
	uint32_t kSubDivision ;
	uint32_t vertexCount;
private:
	void CreateVartexData();
	void SetColor();
	void TransformMatrix();
};

