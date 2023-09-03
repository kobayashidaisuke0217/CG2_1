#pragma once
#include "DirectXCommon.h"
#include"Vector4.h"
#include "BlueMoon.h"
#include "worldTransform.h"
#include "Texturemanager.h"
class Sprite
{
public:
	void Initialize(const Vector4& a, const Vector4& b,const DirectionalLight& light);


	//void Draw( const Transform& transform, const Transform& uvTransform, const  Vector4& material, uint32_t texIndex );
	void Draw(const WorldTransform& transform, const Transform& uvTransform, const  Vector4& material, uint32_t texIndex);
	void Finalize();
private:
	
	DirectXCommon* dxCommon_;
	Texturemanager* textureManager_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	VertexData* vertexData_;
	
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	Material* materialData_;
	BlueMoon* engine_;
	DirectionalLight* directionalLight_;
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};
	uint32_t* indexData_;
private:
	void CreateVartexData(const Vector4& a, const Vector4& b);
	void CreateTransform();
	void SetColor();
	void CreateDictionalLight(const DirectionalLight& light);
};

