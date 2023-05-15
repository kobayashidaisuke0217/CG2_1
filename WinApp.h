#pragma once
#include <Windows.h>
#include <cstdint>

class WinApp
{
public: 
	
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;
	
	static inline HWND GetHwnd() { return hwnd_; }
	HINSTANCE GetHInstance()const { return wc_.hInstance; }
static	bool Procesmessage();
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
static	void CreateGameWindow(
		const wchar_t*title=L"DirectXGame",
		int32_t clientWidth=kClientWidth,int32_t clientheight=kClientHeight
	    
	);
	private:
	static	inline WNDCLASS wc_{};
	static	inline 	RECT wrc_ = { 0,0,kClientHeight,kClientHeight };
	static	HWND hwnd_;
	static	UINT windowStyle_;
};

