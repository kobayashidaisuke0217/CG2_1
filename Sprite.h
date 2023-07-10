#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
#include "base/MyEngine.h"
class Sprite
{
public:
	void Initialize(DirectXCommon* dxCommon, MyEngine* engine);


	void Draw(const Vector4& a, const Vector4& b, const Transform& transform, const Vector4& material, uint32_t texIndex);
	void Finalize();
private:
	
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	ID3D12Resource* vertexResource;
	VertexData* vertexData_;
	ID3D12Resource* transformationMatrixResource;
	Matrix4x4* transformationMatrixdata;
	ID3D12Resource* materialResource_;
	Material* materialData_;
	MyEngine* engine_;
private:
	void CreateVartexData();
	void CreateTransform();
	void SetColor();
};

