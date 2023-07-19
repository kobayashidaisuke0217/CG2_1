#pragma once
#include<base/DirectXCommon.h>
#include"Vector4.h"

class MyEngine;

class Triangle
{
public:
	void Initialize(DirectXCommon* direct,MyEngine* engine);
	void Draw(const Vector4& a,const Vector4& b,const Vector4& c, const Vector4 & material ,const Transform& transform, const Transform& cameraTransform,  const DirectionalLight& light);
	void Finalize();
	
private:
	void SettingVertex();
	void SetColor();
	void TransformMatrix();
	void CreateDictionalLight();
private:
	MyEngine* Engine;
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

