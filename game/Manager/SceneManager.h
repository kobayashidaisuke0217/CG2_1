#pragma once
#include <game/Scenes/Iscene.h>
#include <base/BlueMoon.h>
#include<game/Scenes/gameScene.h>
#include <game/Scenes/TitleScene.h>
#include "Input/Input.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	void Run();
	void Init();
private:
	BlueMoon* Engine;
	WinApp* winApp_ = nullptr;
	Input* input ;
	std::unique_ptr<Iscene> sceneArr_[2];
	int sceneNum_;
	int preSceneNum_;

};
