#include "gameScene.h"

void GameScene::Initialize(MyEngine*engine,DirectXCommon* direct)
{
	engine_ = engine;
	
	directX_ = direct;
	data1_[0] = { -0.5f,-0.5f,0.5f,1.0f };
	data2_[0] = { 0.0f,0.0f,0.0f,1.0f };
	data3_[0] = { 0.5f,-0.5f,-0.5f,1.0f };

	data1_[1] = { -0.5f,-0.5f,0.0f,1.0f };
	data2_[1] = { 0.0f,0.5f,0.0f,1.0f };
	data3_[1] = { 0.5f,-0.5f,0.0f,1.0f };
	material[0] = { 1.0f,1.0f,1.0f,1.0f };
	material[1] = { 1.0f,1.0f,1.0f,1.0f };
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };

	spritedataLeftTop_[0] = {0.0f,0.0f,0.0f,1.0f};
	spritedataRightDown_[0] = {320.0f,180.0f,0.0f,1.0f};
	spriteTransform_ [0] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};

	spritedataLeftTop_[1] = {960.0f,540.0f,0.0f,1.0f};
	spritedataRightDown_[1] = {1280.0f,720.0f,0.0f,1.0f};
	spriteTransform_ [1] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	spriteMaterial[0] = {1.0f,1.0f,1.0f,1.0f};
	engine_->LoadTexture("Resource/uvChecker.png");
	for (int i = 0; i < 2; i++) {
		triangle_[i] = new Triangle();
		triangle_[i]->Initialize(directX_,engine_);
		sprite_[i] = new Sprite();
		sprite_[i]->Initialize(directX_,engine_);
	}

}

void GameScene::Update()
{
	transform_.rotate.y += 0.01f;
	worldMatrix_ = MakeAffineMatrix(transform_.scale, transform_.rotate, transform_.translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(directX_->GetWin()->kClientWidth) / float(directX_->GetWin()->kClientHeight), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix_, Multiply(viewMatrix, projectionMatrix));

	worldMatrix_ = worldViewProjectionMatrix;
	ImGui::Begin("Window");
	ImGui::DragFloat3("CameraTranslate", &cameraTransform_.translate.x, 0.01f);
	ImGui::DragFloat3("spritetranslate", &spriteTransform_[0].translate.x, 0.1f);
	ImGui::End();
}

void GameScene::Draw3D()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Draw(data1_[i], data2_[i], data3_[i],material[i],worldMatrix_);
	}
}
void GameScene::Draw2D() {
	for (int i = 0; i < 1; i++) {
		sprite_[i]->Draw(spritedataLeftTop_[i], spritedataRightDown_[i], spriteTransform_[i],spriteMaterial[0]);
	}
	
}
void GameScene::Finalize()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Finalize();
		sprite_[i]->Finalize();
	}
	
}
