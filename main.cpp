#include "base/MyEngine.h"
#include"gameScene.h"
//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win_ = nullptr;
	MyEngine* Engine = new MyEngine;
	Engine->Initialize(win_, 1280, 720);

	GameScene* gameScene = new GameScene();
	gameScene->Initialize(Engine->GetDirectXCommon());
	//Engine->variableInitialize();
	while (true) {
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}


		Engine->BeginFrame();

		gameScene->Update();
		Engine->Draw();
		gameScene->Draw();
		

		Engine->EndFrame();
	}
	gameScene->Finalize();
	Engine->Finalize();
	return 0;
}
