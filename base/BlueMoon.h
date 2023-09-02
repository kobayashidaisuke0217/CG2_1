#pragma once
#include "DirectXCommon.h"
#include <dxcapi.h>
#include"Vector4.h"
#pragma comment(lib,"dxcompiler.lib")
#include "ImGuiManger.h"
#include"externals/DirectXTex/d3dx12.h"
#include<vector>
class BlueMoon
{
public:
	static const int maxtex =  5;
	static BlueMoon* GetInstance();

	void variableInitialize();
	void Initialize( int32_t width, int32_t height);
	void BeginFrame();
	void EndFrame();
	void Finalize();
	void Update();
	void Draw();
	~BlueMoon();
 
	DirectXCommon* GetDirectXCommon() { return direct_; }
	void LoadTexture(const std::string& filePath,uint32_t index);
	
	
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_[maxtex];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_[maxtex];

	D3D12_CPU_DESCRIPTOR_HANDLE GettextureSrvHandleCPU(ID3D12DescriptorHeap* descriptorheap,uint32_t descriptorSize,uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GettextureSrvHandleGPU(ID3D12DescriptorHeap* descriptorheap, uint32_t descriptorSize, uint32_t index);
private:

	
	 WinApp* win_;
	DirectXCommon* direct_;

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
  ImGuiManger* imguiManager_;
  
 
  Microsoft::WRL::ComPtr<ID3D12Resource>intermediateResource[maxtex];
	IDxcUtils* dxcUtils_;
	IDxcCompiler3* dxcCompiler_;
	IDxcIncludeHandler* includeHandler_;
	
	Microsoft::WRL::ComPtr<ID3DBlob>signatureBlob_;
	
	Microsoft::WRL::ComPtr<ID3DBlob>errorBlob_;
	
	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature_;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};
	D3D12_BLEND_DESC blendDesc_{};
	IDxcBlob* vertexShaderBlob_;
	IDxcBlob* pixelShaderBlob_;
	D3D12_RASTERIZER_DESC rasterizerDesc_{};
	
	Microsoft::WRL::ComPtr<ID3D12PipelineState>graphicsPipelineState_;

	D3D12_VIEWPORT viewport_{};
	D3D12_RECT scissorRect_{};
	D3D12_INPUT_ELEMENT_DESC inputElementDescs_[3];
	//頂点リソースにデータを書き込む
	Vector4* vertexData_;

	
	Microsoft::WRL::ComPtr<ID3D12Resource>textureResource[maxtex];
	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;


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
	void SettingDepth();

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadtextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, uint32_t index);
	DirectX::ScratchImage  LoadTexture(const std::string& filePath);
};
 

