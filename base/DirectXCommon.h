#pragma once
#include <chrono>
#include <cstdlib>
#include <dxgi1_6.h>
#include "WinApp.h"
#include"combert.h"
#include "/Desktop/LE2B/CG2/CG2_1/externals/DirectXTex/DirectXTex.h"

class DirectXCommon
{
public:

	void Initialize(
		WinApp* win, int32_t backBufferWidth = WinApp::kClientWidth,
		int32_t backBufferHeight = WinApp::kClientHeight);
	static void ImGuiInitialize();
	void PreDraw();
	void PostDraw();
	static inline void ClearRenderTarget();
	static void Finalize();
	HRESULT GetHr() { return  hr_; }
	void SetHr(HRESULT a) { this->hr_ = a; }
	ID3D12Device* GetDevice() { return device_; }
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }
	
private:
	static	WinApp* winApp_;
	static IDXGIAdapter4* useAdapter_;
	static	IDXGIFactory7* dxgiFactory_;
	static	ID3D12Device* device_;
	static	ID3D12CommandQueue* commandQueue_;
	static	ID3D12CommandAllocator* commandAllocator_;
	static	ID3D12GraphicsCommandList* commandList_;
	static DXGI_SWAP_CHAIN_DESC1 swapChainDesc_;
	static	IDXGISwapChain4* swapChain_;
	static D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_;
	static	ID3D12DescriptorHeap* rtvDescriptorHeap_;
	static ID3D12DescriptorHeap* srvDescriptorHeap_;
	//RTVを２つ作るのでディスクリプタを２つ用意
	static	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];
	static	ID3D12Resource* backBuffers_[2];
	
	
	static	UINT64 fenceVal_;
	static	int32_t backBufferWidth_;
	static	int32_t backBufferHeight_;
	static	inline D3D12_RESOURCE_BARRIER barrier_{};
	//初期値０でFenceを作る
	static	ID3D12Fence* fence_;
	static	HANDLE fenceEvent_;
	static HRESULT hr_;
	ID3D12DescriptorHeap* CreateDescriptionHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescripters, bool shaderVisible);
private:


	void InitializeDXGIDevice();
	void CreateSwapChain();
	void InitializeCommand();
	void CreateFinalRenderTargets();
	void CreateFence();
	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
};

