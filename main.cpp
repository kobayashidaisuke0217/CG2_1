//#include <Windows.h>
#include <cstdint>
//#include <string>
#include "WinApp.h"




//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* win_ = nullptr;
	win_->CreateGameWindow(L"CG2",1280,720);
	while (true) {
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}
		
	}
	return 0;
}
