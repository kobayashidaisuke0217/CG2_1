#pragma once
#include "DirectXCommon.h"
#include <dxcapi.h>
#include"Vector4.h"
#pragma comment(lib,"dxcompiler.lib")
#include "ImGuiManger.h"

#include<vector>
class BlueMoon
{
public:

	static BlueMoon* GetInstance();

	void variableInitialize();
	void Initialize(int32_t width, int32_t height);
	void BeginFrame();
	void EndFrame();
	void Finalize();
	void Update();
	void Draw();
	~BlueMoon();

	DirectXCommon* GetDirectXCommon() { return direct_; }





private:


	WinApp* win_;
	DirectXCommon* direct_;

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	ImGuiManger* imguiManager_;



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


};



