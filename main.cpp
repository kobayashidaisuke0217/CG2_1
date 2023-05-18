//#include <Windows.h>
//#include <cstdint>
//#include <string>
//#include "WinApp.h"
//#include"base/DirectXCommon.h"
#include "base/MyEngine.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win_ = nullptr;
	MyEngine* Engine = nullptr;
	Engine->Initialize(win_, 1280, 720);
	
	Vector4 data[3];
	data[0] = { -0.4f,-0.4f,0.0f,1.0f };
	data[1] = { 0.0f,0.0f,0.0f,1.0f };
	data[2] = { 0.4f,0.0f,0.0f,1.0f };
	Vector4 data2[3];
	data2[0] = { 0.2f,0.2f,0.0f,1.0f };
	data2[1] = { 0.0f,0.5f,0.0f,1.0f };
	data2[2] = { 0.7f,0.2f,0.0f,1.0f };
   
	
	while (true) {

		MyEngine::BeginFrame();
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}
	

		MyEngine::DrawTriangle(data2[0], data2[1], data2[2]);
		MyEngine::DrawTriangle(data[0], data[1], data[2]);
		MyEngine::EndFrame();
	}
	
	Engine->Finalize();
	return 0;
}
