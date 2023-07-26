#include "SceneManager.h"

SceneManager::SceneManager()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	 Engine = MyEngine::GetInstance();
	Engine->Initialize(win_, 1280, 720);

	
	sceneArr_[TITLE_SCENE]=std::make_unique<TitleScene>();
	sceneArr_[GAME_SCENE]= std::make_unique<GameScene>();
	sceneNum_ = TITLE_SCENE;
}
void SceneManager::Run() {
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
		}
		sceneArr_[sceneNum_]->Update();

		sceneArr_[sceneNum_]->Draw();
		/*gameScene->Update();

		gameScene->Draw3D();
		gameScene->Draw2D();*/

		Engine->Draw();
		Engine->EndFrame();
	}
}

void SceneManager::Finalize()
{
	Engine->Finalize();
	
}
