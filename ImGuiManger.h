#pragma once
#include "base/DirectXCommon.h"
class ImGuiManger
{
public:
	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);
	void Finalize();
	void Begin();
	void End();
	void Draw();
private:
	DirectXCommon* dxCommon_;
	ID3D12DescriptorHeap* srvDescriptorHeap_;
};

