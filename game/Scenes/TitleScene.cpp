#include "TitleScene.h"
#include<base/ImGuiManger.h>
void TitleScene::Initialize()
{
	count = 0;
}

void TitleScene::Update()
{
	count++;
	ImGui::Begin("SceneManager");
	ImGui::InputInt("SceneNum", &sceneNum);
	ImGui::End();
	/*if (count >= 60) {
		sceneNum=GAME_SCENE;
	}*/
}

void TitleScene::Draw()
{
}

void TitleScene::Finalize()
{
}
