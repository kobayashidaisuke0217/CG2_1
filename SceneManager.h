#pragma once
#include"Iscene.h"
#include "base/BlueMoon.h"
#include"gameScene.h"
#include "TitleScene.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	void Run();
	void Init();
private:
	BlueMoon* Engine;
	WinApp* win_ = nullptr;
	std::unique_ptr<Iscene> sceneArr_[2];
	int sceneNum_;
	int preSceneNum_;

};

