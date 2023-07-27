#pragma once
#include"Iscene.h"
#include "base/MyEngine.h"
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
	MyEngine* Engine;
	WinApp* win_ = nullptr;
	std::unique_ptr<Iscene> sceneArr_[2];
	int sceneNum_;
	int preSceneNum_;

};

