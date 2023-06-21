#include "ImGuiManger.h"

void ImGuiManger::Initialize(WinApp* winApp, DirectXCommon* dxCommon)
{
	dxCommon_ = dxCommon;
	srvDescriptorHeap_ = dxCommon_->CreateDescriptionHeap(dxCommon_->GetDevice(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 128, true);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(dxCommon_->GetDevice(),
		dxCommon_->GetbackBufferCount(),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		srvDescriptorHeap_,
		srvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvDescriptorHeap_->GetGPUDescriptorHandleForHeapStart());
}

void ImGuiManger::Finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	srvDescriptorHeap_->Release();
}

void ImGuiManger::Begin()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManger::End()
{
	ImGui::Render();
	
}

void ImGuiManger::Draw()
{
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescriptorHeap_ };
	dxCommon_->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dxCommon_->GetCommandList());
	
}
