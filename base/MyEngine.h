#pragma once
#include "DirectXCommon.h"
#include <dxcapi.h>
#include"Vector4.h"
#pragma comment(lib,"dxcompiler.lib")
#include <ImGuiManger.h>
#include"externals/DirectXTex/d3dx12.h"
#include<vector>
//#include <TextureManager.h>
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
 //void Loadtexture(const std::string& filePath) { textureManager_->LoadTexture( filePath); }
	DirectXCommon* GetDirectXCommon() { return direct_; }
	void LoadTexture(const std::string& filePath);
	D3D12_CPU_DESCRIPTOR_HANDLE GettextureSrvHandleCPU() { return textureSrvHandleCPU_; }
	D3D12_GPU_DESCRIPTOR_HANDLE GettextureSrvHandleGPU() { return textureSrvHandleGPU_; }
private:
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_;
	static WinApp* win_;
	static	DirectXCommon* direct_;
  ImGuiManger* imguiManager_;
  //TextureManager* textureManager_;
  ID3D12Resource* intermediateResource;
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
	

	D3D12_VIEWPORT viewport_{};
	D3D12_RECT scissorRect_{};
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[2];
	//頂点リソースにデータを書き込む
	Vector4* vertexData_;

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


	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);  
	void UploadtextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
	DirectX::ScratchImage  SendTexture(const std::string& filePath);
};


