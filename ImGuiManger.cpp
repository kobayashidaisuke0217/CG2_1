#include "ImGuiManger.h"

void ImGuiManger::Initialize(WinApp* winApp, DirectXCommon* dxCommon)
{
	dxCommon_ = dxCommon;
	 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(dxCommon_->GetDevice(),
		dxCommon_->GetbackBufferCount(),
		dxCommon_->getRtvDesc().Format,
		dxCommon_->GetSrvHeap(),
		dxCommon_->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart(),
		dxCommon_->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart());
}

void ImGuiManger::Finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

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
