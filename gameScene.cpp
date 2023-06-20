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
	material[0] = { 1.0f,1.0f,0.1f,1.0f };
	material[1] = { 1.0f,0.1f,1.0f,1.0f };
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	for (int i = 0; i < 2; i++) {
		triangle_[i] = new Triangle();
		triangle_[i]->Initialize(directX_);
	}

}

void GameScene::Update()
{
	worldMatrix_ = MakeAffineMatrix(transform_.scale, transform_.rotate, transform_.translate);
}

void GameScene::Draw()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Draw(data1_[i], data2_[i], data3_[i],material[i],worldMatrix_);
	}
}

void GameScene::Finalize()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Finalize();
	}
}
