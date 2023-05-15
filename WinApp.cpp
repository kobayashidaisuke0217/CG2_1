#include "WinApp.h"

#include<string>
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
void WinApp::CreateGameWindow(const wchar_t* title, int32_t clientWidth, int32_t clientheight)
{
	wc_.lpfnWndProc = WindowProc;
	wc_.lpszClassName = L"CG2WINDOWClass";
	wc_.hInstance = GetModuleHandle(nullptr);
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClass(&wc_);
	AdjustWindowRect(&wrc_, WS_OVERLAPPEDWINDOW, false);
	hwnd_ = CreateWindow(
		wc_.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,//表示X座標
		CW_USEDEFAULT,//表示Y座標
		wrc_.right - wrc_.left,//ウィンドウ横幅
		wrc_.bottom - wrc_.top,//ウィンドウ縦幅
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		wc_.hInstance,//インスタンスハンドル
		nullptr//オプション
	);
#ifdef _DEBUG
		ID3D12Debug1 * debugController = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		//デバッグレイヤーを有効化する
		debugController->EnableDebugLayer();
		//さらにGPU側でもチェックを行うようにする
		debugController->SetEnableGPUBasedValidation(true);
	}
#endif  
	ShowWindow(hwnd_, SW_SHOW);
	
}

bool WinApp::Procesmessage() {
	MSG msg{};
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return false;
}


HWND WinApp::hwnd_;
UINT WinApp::windowStyle_;