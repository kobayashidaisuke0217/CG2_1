#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
#include "base/MyEngine.h"
class Sphere
{
public:
	void Initialize(DirectXCommon* dxCommon, MyEngine* engine);


	void Draw(const Vector4& material, const Transform& wvpdata, uint32_t texIndex, const Transform& cameratransform, const DirectionalLight& light);
	void Finalize();
private:
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	ID3D12Resource* vertexResource;
	VertexData* vertexData_;
	
	ID3D12Resource* wvpResource_;
	Transformmatrix* wvpData_;
	ID3D12Resource* materialResource_;
	Material* materialData_;
	MyEngine* engine_;
	const float pi = 3.14159265358979f;
	uint32_t kSubDivision ;
	uint32_t vertexCount;
	DirectionalLight* directionalLight_; 
	ID3D12Resource* directionalLightResource_;
private:
	void CreateVartexData();
	void SetColor();
	void TransformMatrix();
	void CreateDictionalLight();
};

