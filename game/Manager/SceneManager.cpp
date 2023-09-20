#include "SceneManager.h"
#include"ImGuiManger.h"
SceneManager::SceneManager()
{
	
	
	
}
SceneManager::~SceneManager()
{

}
void SceneManager::Run() {
	Init();

	while (true) {
		// メッセージ処理
		if (winApp_->Procesmessage()) {
			break;
		}

		
		blueMoon_->BeginFrame();
		input->Update();
		preSceneNum_ = sceneNum_;
		sceneNum_ = sceneArr_[sceneNum_]->GetSceneNum();

		if (sceneNum_ != preSceneNum_) {
			sceneArr_[preSceneNum_]->Finalize();
			sceneArr_[sceneNum_]->Initialize();
			
		}
		sceneArr_[sceneNum_]->Update();

		
		sceneArr_[sceneNum_]->Draw();
		

		blueMoon_->Draw();
		blueMoon_->EndFrame();
	}
	CoUninitialize();
	blueMoon_->Finalize();
	sceneArr_[sceneNum_]->Finalize();
	
}

void SceneManager::Init()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	blueMoon_ = BlueMoon::GetInstance();
	blueMoon_->Initialize( 1280, 720);
	winApp_ = WinApp::GetInstance();

	sceneArr_[TITLE_SCENE] = std::make_unique <TitleScene>();
	sceneArr_[GAME_SCENE] = std::make_unique <GameScene>();
	sceneNum_ = TITLE_SCENE;
	sceneArr_[sceneNum_]->Initialize();
	input=Input::GetInstance();
	input->Initialize(winApp_);
	textureManager_ = Texturemanager::GetInstance();
	textureManager_->Initialize();
}


