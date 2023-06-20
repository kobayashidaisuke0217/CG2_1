#include "gameScene.h"

void GameScene::Initialize(DirectXCommon* direct)
{
	directX_ = direct;
	data1_[0] = { -0.2f,-0.1f,0.0f,1.0f };
	data2_[0] = { -0.15f,0.1f,0.0f,1.0f };
	data3_[0] = { -0.1f,-0.1f,0.0f,1.0f };

	data1_[1] = { -0.2f,-0.3f,0.0f,1.0f };
	data2_[1] = { -0.15f,-0.1f,0.0f,1.0f };
	data3_[1] = { -0.1f,-0.3f,0.0f,1.0f };

	

	for (int i = 0; i < 2; i++) {
		triangle_[i] = new Triangle();
		triangle_[i]->Initialize(directX_);
	}

}

void GameScene::Update()
{
}

void GameScene::Draw()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Draw(data1_[i], data2_[i], data3_[i]);
	}
}

void GameScene::Finalize()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Finalize();
	}
}
