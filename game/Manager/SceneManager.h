#pragma once
#pragma region エンジン
#include "BlueMoon.h"
#include "Input/Input.h"
#include "Texturemanager.h"
#pragma endregion
#pragma region シーン
#include <game/Scenes/Iscene.h>
#include<game/Scenes/gameScene.h>
#include <game/Scenes/TitleScene.h>
#pragma endregion
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	void Run();
	void Init();
private:
	BlueMoon* blueMoon_;
	WinApp* winApp_ = nullptr;
	Input* input ;
	Texturemanager* textureManager_;
	std::unique_ptr<Iscene> sceneArr_[2];
	int sceneNum_;
	int preSceneNum_;

};

