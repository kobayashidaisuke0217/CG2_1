#pragma once
#include <chrono>
#include <cstdlib>
#include <dxgi1_6.h>
#include "WinApp.h"
#include"combert.h"
#include"externals/DirectXTex/DirectXTex.h"
class DirectXCommon
{
public:

	void Initialize(
		WinApp* win, int32_t backBufferWidth = WinApp::kClientWidth,
		int32_t backBufferHeight = WinApp::kClientHeight);

	void PreDraw();
	void PostDraw();
	 void ClearRenderTarget();
	 void Finalize();
	HRESULT GetHr() { return  hr_; }
	void SetHr(HRESULT a) { this->hr_ = a; }
	ID3D12Device* GetDevice() { return device_; }
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }
	static ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	WinApp* GetWin() { return winApp_;}
	UINT GetbackBufferCount() { return swapChainDesc.BufferCount ; }
	ID3D12DescriptorHeap* CreateDescriptionHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescripters, bool shaderVisible);
	ID3D12DescriptorHeap* GetSrvHeap() { return srvDescriptorHeap_; }
	ID3D12DescriptorHeap* GetDsvHeap() { return dsvDescriptorHeap_; }
	D3D12_RENDER_TARGET_VIEW_DESC getRtvDesc() {return rtvDesc;}
	
private:
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	ID3D12DescriptorHeap* srvDescriptorHeap_;
	ID3D12DescriptorHeap* dsvDescriptorHeap_;
		WinApp* winApp_;
	 IDXGIAdapter4* useAdapter_;
		IDXGIFactory7* dxgiFactory_;
		ID3D12Device* device_;
		ID3D12CommandQueue* commandQueue_;
		ID3D12CommandAllocator* commandAllocator_;
		ID3D12GraphicsCommandList* commandList_;
		IDXGISwapChain4* swapChain_;
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
		ID3D12DescriptorHeap* rtvDescriptorHeap_;
	//RTVを２つ作るのでディスクリプタを２つ用意
		D3D12_CPU_DESCRIPTOR_HANDLE dsvhandle;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];
		ID3D12Resource* backBuffers_[2];//(swapChainResources???)
		UINT64 fenceVal_;
		int32_t backBufferWidth_;
		int32_t backBufferHeight_;
		 D3D12_RESOURCE_BARRIER barrier_{};
	//初期値０でFenceを作る
		ID3D12Fence* fence_;
		HANDLE fenceEvent_;
	 HRESULT hr_;
	 ID3D12Resource* depthStencilResource;
private:


	void InitializeDXGIDevice();
	void CreateSwapChain();
	void InitializeCommand();
	void CreateFinalRenderTargets();
	void CreateFence();
	void CreateSrvheap();
	ID3D12Resource* CreateDepthStenciltextureResource(ID3D12Device* device,int32_t width,int32_t height);
	void CreateDepthStensil();
};

