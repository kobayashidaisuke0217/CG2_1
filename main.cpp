#include "MyEngine.h"
//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	MyEngine::Initialize(L"DirectX",1280,720);

	while (WinApp::Procesmessage()==0)
	{
		MyEngine::BeginFrame();

	//	MyEngine::DrawTriangle(10, 10, 30, 30, 15, 15);
		MyEngine::EndFrame();
	}
	MyEngine::Finalize();

	return 0;
}

