//#include <Windows.h>
//#include <cstdint>
//#include <string>
//#include "WinApp.h"
#include"base/DirectXCommon.h"



//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	DirectXCommon* direct=nullptr;
	
	WinApp* win_ = nullptr;
	direct->Initialize(win_,1280,720);
	//win_->CreateGameWindow(L"CG2",1280,720);
	while (true) {
		direct->PreDraw();
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}
		
	direct->PostDraw();
		//direct->ClearRenderTarget();
	}
	direct->Finalize();
	return 0;
}
