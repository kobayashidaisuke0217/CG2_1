#pragma once
#include<base/DirectXCommon.h>
#include"Vector4.h"

class BlueMoon;

class Triangle
{
public:
	void Initialize(  const DirectionalLight& light);
	void Draw(const Transform& transform, const Transform& cameraTransform, const Vector4& material);
	void Finalize();
	
private:
	void SettingVertex();
	void SetColor();
	void TransformMatrix();
	void CreateDictionalLight(const DirectionalLight& light);
private:
	BlueMoon* Engine;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	DirectXCommon* direct_;
	VertexData* vertexData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

	Material *materialData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	DirectionalLight* directionalLight_;
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
};

