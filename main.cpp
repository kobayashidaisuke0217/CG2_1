//#include <Windows.h>
//#include <cstdint>
//#include <string>
//#include "WinApp.h"
#include"base/DirectXCommon.h"
#//include "base/MyEngine.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win_ = nullptr;
	/*MyEngine* Engine = nullptr;
	Engine->Initialize(win_, 1280, 720);*/
	DirectXCommon* direct = nullptr;
	direct->Initialize(win_, 1280, 720);
	
	
	//win_->CreateGameWindow(L"CG2",1280,720);
	while (true) {

		//MyEngine::BeginFrame();
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}
		direct->PreDraw();
		//direct->PostDraw();
		//MyEngine::EndFrame();
	}
	//direct->Finalize();
	//Engine->Finalize();
	return 0;
}
