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

		
		Engine->BeginFrame();
		input->Update();
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
	//Engine->Finalize();
	sceneArr_[sceneNum_]->Finalize();
	
}

void SceneManager::Init()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	Engine = BlueMoon::GetInstance();
	Engine->Initialize( 1280, 720);
	winApp_ = WinApp::GetInstance();

	sceneArr_[TITLE_SCENE] = std::make_unique <TitleScene>();
	sceneArr_[GAME_SCENE] = std::make_unique <GameScene>();
	sceneNum_ = TITLE_SCENE;
	sceneArr_[sceneNum_]->Initialize();
	input=Input::GetInstance();
	input->Initialize(winApp_);
}


