#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
#include "base/MyEngine.h"
class Sphere
{
public:
	void Initialize(DirectXCommon* dxCommon, MyEngine* engine, const DirectionalLight& light);


	void Draw(const Vector4& material, const Transform& transform, uint32_t texIndex, const Transform& cameraTransform);
	void Finalize();
private:
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	VertexData* vertexData_;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	Material* materialData_;
	MyEngine* engine_;
	const float pi = 3.14159265358979f;
	uint32_t kSubDivision;
	uint32_t vertexCount;
	DirectionalLight* directionalLight_; 
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
	//D3D12_INDEX_BUFFER_VIEW indexBufferView{};
	//uint32_t* indexData_;
	//ID3D12Resource* indexResource_;
private:
	void CreateVartexData();
	void SetColor();
	void TransformMatrix();
	void CreateDictionalLight(const DirectionalLight& light);
};

