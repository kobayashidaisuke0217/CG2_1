#include "base/MyEngine.h"
#include"gameScene.h"
#include "SceneManager.h"
//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CoInitializeEx(0, COINIT_MULTITHREADED);
	WinApp* win_ = nullptr;
	MyEngine* Engine = new MyEngine;
	Engine->Initialize(win_, 1280, 720);

	GameScene* gameScene = new GameScene();
	gameScene->Initialize(Engine,Engine->GetDirectXCommon());
	

	while (true) {
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}


		Engine->BeginFrame();

		gameScene->Update();

		gameScene->Draw3D();
		gameScene->Draw2D();
		
		Engine->Draw();
		Engine->EndFrame();
	}
	gameScene->Finalize();
	Engine->Finalize();
	delete gameScene;
	CoUninitialize();
	
	//delete win_;
	
	delete Engine;
	/*Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		
	}*/
	return 0;
}
