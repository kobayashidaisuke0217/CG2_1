#include "gameScene.h"

void GameScene::Initialize(MyEngine*engine,DirectXCommon* direct)
{
	engine_ = engine;
	
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
	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
	engine_->LoadTexture("Resource/uvChecker.png");
	for (int i = 0; i < 2; i++) {
		triangle_[i] = new Triangle();
		triangle_[i]->Initialize(directX_,engine_);
	}

}

void GameScene::Update()
{
	worldMatrix_ = MakeAffineMatrix(transform_.scale, transform_.rotate, transform_.translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(directX_->GetWin()->kClientWidth) / float(directX_->GetWin()->kClientHeight), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix_, Multiply(viewMatrix, projectionMatrix));

	worldMatrix_ = worldViewProjectionMatrix;
	ImGui::Begin("Window");
	ImGui::DragFloat3("CameraTranslate", &cameraTransform_.translate.x, 0.01f);

	ImGui::End();
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
