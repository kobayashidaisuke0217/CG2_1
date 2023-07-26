#include "TitleScene.h"

void TitleScene::Initialize()
{
	count = 0;
}

void TitleScene::Update()
{
	count++;
	if (count >= 60) {
		sceneNum=GAME_SCENE;
	}
}

void TitleScene::Draw()
{
}
