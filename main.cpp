#include "base/MyEngine.h"
#include"base/DrawTriangle.h"
//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win_ = nullptr;
	MyEngine* Engine = new MyEngine;
	Engine->Initialize(win_, 1280, 720);
	
   
	Engine->variableInitialize();
	while (true) {
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}
		
		Engine->Update();
		Engine->BeginFrame();
	
		Engine->Draw();
		
		Engine->EndFrame();
	}
	
	Engine->Finalize();
	return 0;
}
