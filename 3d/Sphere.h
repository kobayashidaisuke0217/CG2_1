#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
#include "base/BlueMoon.h"
#include "worldTransform.h"
#include "ViewProjection.h"
class Sphere
{
public:
	void Initialize();


	//void Draw(const Vector4& material, const Transform& transform, uint32_t texIndex, const Transform& cameraTransform, const DirectionalLight& light);
	void Draw(const Vector4& material, const WorldTransform& transform, uint32_t texIndex, const ViewProjection& viewProjection, const DirectionalLight& light);
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
	BlueMoon* engine_;
	const float pi = 3.14159265358979f;
	uint32_t kSubDivision;
	uint32_t vertexCount;
	DirectionalLight* directionalLight_; 
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
	

private:
	void CreateVartexData();
	void SetColor();
	void TransformMatrix();
	void CreateDictionalLight();
};

