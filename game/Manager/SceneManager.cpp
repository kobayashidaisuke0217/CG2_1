#include "SceneManager.h"
#include"ImGuiManger.h"
SceneManager::SceneManager()
{
	
	
	
}
SceneManager::~SceneManager()
{
	audio_->xAudio2.Reset();
	audio_->SoundUnload(&audio_->soundDatas[0]);
}
void SceneManager::Run() {
	Initialize();

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
		if (input->PushKey(DIK_1)) {
			audio_->SoundPlayWave(audio_->xAudio2.Get(), audio_->soundDatas[0]);
		}
		
		sceneArr_[sceneNum_]->Draw();
		

		blueMoon_->Draw();
		blueMoon_->EndFrame();
	}
	CoUninitialize();
	blueMoon_->Finalize();
	sceneArr_[sceneNum_]->Finalize();
	
}

void SceneManager::Initialize()
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
	audio_ = Audio::GetInstance();
	audio_->Initialize();
	audio_->soundDatas[0] = audio_->SoundLoadWave("resource/Alarm01.wav");
}


