#pragma once
#include <chrono>
#include <cstdlib>
#include <dxgi1_6.h>
#include "WinApp.h"
#include"combert.h"

class DirectXCommon
{
public:

	void Initialize(
		WinApp* win, int32_t backBufferWidth = WinApp::kClientWidth,
		int32_t backBufferHeight = WinApp::kClientHeight);

	void PreDraw();
	void PostDraw();
	static inline void ClearRenderTarget();
	static void Finalize();
	HRESULT GetHr() { return  hr_; }
	void SetHr(HRESULT a) { this->hr_ = a; }
	ID3D12Device* GetDevice() { return device_; }
	ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }
	//int32_t GetBackBufferWidth() const;
	//int32_t GetBackBufferHeight() const;
	//size_t GetBackBufferCount() const { return backBuffers_.size(); }
private:
	static	WinApp* winApp_;
	static IDXGIAdapter4* useAdapter_;
	static	IDXGIFactory7* dxgiFactory_;
	static	ID3D12Device* device_;
	static	ID3D12CommandQueue* commandQueue_;
	static	ID3D12CommandAllocator* commandAllocator_;
	static	ID3D12GraphicsCommandList* commandList_;
	static	IDXGISwapChain4* swapChain_;
	static	ID3D12DescriptorHeap* rtvDescriptorHeap_;
	//RTVを２つ作るのでディスクリプタを２つ用意
	static	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];
	static	ID3D12Resource* backBuffers_[2];//(swapChainResources???)
	static	UINT64 fenceVal_;
	static	int32_t backBufferWidth_;
	static	int32_t backBufferHeight_;
	static	inline D3D12_RESOURCE_BARRIER barrier_{};
	//初期値０でFenceを作る
	static	ID3D12Fence* fence_;
	static	HANDLE fenceEvent_;
	static HRESULT hr_;
private:


	void InitializeDXGIDevice();
	void CreateSwapChain();
	void InitializeCommand();
	void CreateFinalRenderTargets();
	void CreateFence();
};

