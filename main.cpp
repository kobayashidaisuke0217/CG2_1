#include <game/Manager/SceneManager.h>

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SceneManager* sceneManager = new SceneManager();
	sceneManager->Run();
	delete sceneManager;
	return 0;
}
