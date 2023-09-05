#pragma once
#include "DirectXCommon.h"
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
	
};

