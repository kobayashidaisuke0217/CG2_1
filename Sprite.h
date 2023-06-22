#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
class Sprite
{
public:
	void Initialize(DirectXCommon* dxCommon);


	void Draw(Vector4 a,Vector4 b, Transform transform);
	void Finalize();
private:
	
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	ID3D12Resource* vertexResource;
	VertexData* vertexData_;
	ID3D12Resource* transformationMatrixResource;
	Matrix4x4* transformationMatrixdata;
private:
	void CreateVartexData();
	void CreateTransform();
};

