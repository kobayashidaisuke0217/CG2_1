#include "SceneManager.h"

SceneManager::SceneManager()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	 Engine = BlueMoon::GetInstance();
	Engine->Initialize(win_, 1280, 720);

	
	sceneArr_[TITLE_SCENE]=new TitleScene();
	sceneArr_[GAME_SCENE]=new GameScene();
}
SceneManager::~SceneManager()
{

}
void SceneManager::Run() {
	Init();

	while (true) {
		// メッセージ処理
		if (win_->Procesmessage()) {
			break;
		}

		
		Engine->BeginFrame();
		preSceneNum_ = sceneNum_;
		sceneNum_ = sceneArr_[sceneNum_]->GetSceneNum();

		if (sceneNum_ != preSceneNum_) {
			sceneArr_[sceneNum_]->Initialize();
			sceneArr_[preSceneNum_]->Finalize();
		}
		sceneArr_[sceneNum_]->Update();

		sceneArr_[sceneNum_]->Draw();
		

		Engine->Draw();
		Engine->EndFrame();
	}
	CoUninitialize();
	Engine->Finalize();
	sceneArr_[sceneNum_]->Finalize();
	delete this;
}

void SceneManager::Init()
{
	sceneNum_ = TITLE_SCENE;

	
}


