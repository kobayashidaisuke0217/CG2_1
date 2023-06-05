#include "base/MyEngine.h"
#include"base/Triangle.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoInitializeEx(0, COINIT_MULTITHREADED);

	WinApp* win_ = nullptr;
	MyEngine* Engine = new MyEngine;
	Engine->Initialize(win_, 1280, 720);


	Engine->variableInitialize();
	while (true) {
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}


		Engine->BeginFrame();

		Engine->Update();

		Engine->Draw();

		Engine->EndFrame();
	}

	Engine->Finalize();
	CoUninitialize();
	return 0;
}