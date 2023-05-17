#pragma once
#include "DirectXCommon.h"
#include <dxgidebug.h>
#include <dxcapi.h>
#include"Vector4.h"
#pragma comment(lib,"dxcompiler.lib")
class MyEngine
{
public:

	static void Initialize(WinApp* win, int32_t width, int32_t height);
	static	void DrawTriangle(float ax, float ay, float bx, float by, float cx, float cy);
	static void BeginFrame();
	static void EndFrame();
	static void Finalize();

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
	static ID3D12Resource* vertexResource_;
	static inline D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	static inline  D3D12_VIEWPORT viewport_{};
	static inline D3D12_RECT scissorRect_{};
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
	static void InitializeDxcCompiler();
	static void CreateRootSignature();
	static void CreateInputlayOut();
	static void SettingBlendState();
	static void SettingRasterizerState();
	static void InitializePSO();
	static void SettingVertex();
	static void SettingViePort();
	static void SettingScissor();

};


