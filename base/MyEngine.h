#pragma once
#include "DirectXCommon.h"
#include <dxcapi.h>
#include"Vector4.h"
#pragma comment(lib,"dxcompiler.lib")
class MyEngine
{
public:

	 void Initialize(WinApp* win, int32_t width, int32_t height);
	static	void DrawTriangle(Vector4& a,Vector4& b,Vector4& c);
	static void BeginFrame();
	static void EndFrame();
	 void Finalize();
private:

	static WinApp* win_;
	static	DirectXCommon* direct_;
	static	IDxcUtils* dxcUtils_;
	static	IDxcCompiler3* dxcCompiler_;
	static	IDxcIncludeHandler* includeHandler_;
	static	ID3DBlob* signatureBlob_;
	static	ID3DBlob* errorBlob_;
	static	ID3D12RootSignature* rootSignature_;
	static inline D3D12_INPUT_LAYOUT_DESC inputLayoutDesc_{};
	static inline D3D12_BLEND_DESC blendDesc_{};
	static	IDxcBlob* vertexShaderBlob_;
	static	IDxcBlob* pixelShaderBlob_;
	static inline D3D12_RASTERIZER_DESC rasterizerDesc_{};
	static	ID3D12PipelineState* graphicsPipelineState_;
	ID3D12Resource* vertexResource_;
	static D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	
	static inline  D3D12_VIEWPORT viewport_{};
	static inline D3D12_RECT scissorRect_{};
	static  D3D12_INPUT_ELEMENT_DESC inputElementDescs_[1];
	//頂点リソースにデータを書き込む
	static Vector4* vertexData_;
	static	IDxcBlob* CompileShader(
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
	 void SettingVertex();
	 void SettingViePort();
	 void SettingScissor();

};


