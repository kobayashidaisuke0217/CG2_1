#pragma once
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>
#pragma comment(lib,"d3d12.lib")
class WinApp
{
public:
	static ID3D12Debug1* GetdebugController() { return debugController_; }

	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	static inline HWND GetHwnd() { return hwnd_; }
	HINSTANCE GetHInstance()const { return wc_.hInstance; }
	static	bool Procesmessage();
	static void Finalize();
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	static	void CreateGameWindow(
		const wchar_t* title ,
		int32_t clientWidth , int32_t clientheight 

	);
private:
	 static ID3D12Debug1* debugController_;
	static	inline WNDCLASS wc_{};
	static	inline 	RECT wrc_ = { 0,0,kClientWidth,kClientHeight };
	static	HWND hwnd_;
	static	UINT windowStyle_;
};