#pragma once
#include "DirectXCommon.h"
#include <dxcapi.h>
#include"Vector4.h"
#include "Triangle.h"
#include <Transform.h>
#pragma comment(lib,"dxcompiler.lib")
#include"externals/DirectXTex/DirectXTex.h"
#include"externals/DirectXTex/d3dx12.h"
#include<vector>
class MyEngine
{
public:
	void variableInitialize();
	void Initialize(WinApp* win, int32_t width, int32_t height);
	void BeginFrame();
	void EndFrame();
	void Finalize();
	void Update();
	void Draw();
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVHandleGPU() { return textureSrvHandleGPU_; }
private:
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;
	static WinApp* win_;
	static	DirectXCommon* direct_;
	DirectX::ScratchImage mipImage;
	IDxcUtils* dxcUtils_;
	IDxcCompiler3* dxcCompiler_;
	IDxcIncludeHandler* includeHandler_;
	ID3DBlob* signatureBlob_;
	ID3DBlob* errorBlob_;
	ID3D12RootSignature* rootSignature_;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};
	D3D12_BLEND_DESC blendDesc_{};
	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;
	D3D12_RASTERIZER_DESC rasterizerDesc_{};
	ID3D12PipelineState* graphicsPipelineState_;
	ID3D12Resource* intermediateResource;
	

	D3D12_VIEWPORT viewport_{};
	D3D12_RECT scissorRect_{};
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[2];
	//頂点リソースにデータを書き込む
	Vector4* vertexData_;


	//三角形のデータ
	Triangle* triangle[3];
	Transform vertexTransform_;
	Matrix4x4 worldMatrix_;
	Vector4 data1[3];
	Vector4 data2[3];
	Vector4 data3[3];
	Vector4 material[3];
	//マトリックスデータ
	Transform cameraTransform_;

	ID3D12Resource* textureResource;

	IDxcBlob* CompileShader(
		//CompileShaderするShaderファイルへのパス
		const std::wstring& filePath,
		//Compielerに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);
	void InitializeDxcCompiler();
	void CreateRootSignature();
	void CreateInputlayOut();
	void SettingBlendState();
	void SettingRasterizerState();
	void InitializePSO();
	
	void SettingViePort();
	void SettingScissor();
	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	ID3D12Resource* UploadtextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
	DirectX::ScratchImage SendTexture(const std::string& filePath);
	void LoadTexture(const std::string& filePath);
};


