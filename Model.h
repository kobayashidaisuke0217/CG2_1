#pragma once
#include "base/DirectXCommon.h"
#include"Vector4.h"
#include "base/MyEngine.h"
#include <string>
class Model
{
public:
	void Initialize(DirectXCommon* dxCommon, MyEngine* engine, const std::string& directoryPath, const std::string& filename, uint32_t index, const DirectionalLight& light);


	void Draw(const Vector4& material, const Transform& transform, uint32_t texIndex, const Transform& cameraTransform);
     ModelData modelData_;
	void Finalize();
	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath,const std::string&filename);
private:
	DirectXCommon* dxCommon_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	VertexData* vertexData_;

	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	Transformmatrix* wvpData_;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	Material* material_;
	MyEngine* engine_;
	
	
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

