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
	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-10.0f} };

	spritedataLeftTop_[0] = {0.0f,0.0f,0.0f,1.0f};
	spritedataRightDown_[0] = {320.0f,180.0f,0.0f,1.0f};
	spriteTransform_ [0] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};

	spritedataLeftTop_[1] = {960.0f,540.0f,0.0f,1.0f};
	spritedataRightDown_[1] = {1280.0f,720.0f,0.0f,1.0f};
	spriteTransform_ [1] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	spriteMaterial[0] = {1.0f,1.0f,1.0f,1.0f};
	sphereTransform_= { {1.0f,1.0f,1.0f},{0.0f,1.6f,0.0f},{0.0f,0.0f,0.0f} };
	sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	SpriteuvTransform =
	{ 
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	sphere_ = new Sphere();
	sphere_->Initialize(directX_, engine_);
	uvResourceNum = 0;
	engine_->LoadTexture("Resource/uvChecker.png",uvResourceNum);
	monsterBallResourceNum = 1;
	engine_->LoadTexture("Resource/monsterBall.png",monsterBallResourceNum);
	directionalLight_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
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
	directionalLight_.direction= Normalise(directionalLight_.direction);
	
	ImGui::Begin("Window");
	ImGui::DragFloat3("CameraTranslate", &cameraTransform_.translate.x, 0.01f);
	ImGui::DragFloat3("spritetranslate", &spriteTransform_[0].translate.x, 0.1f);
	ImGui::DragFloat3("spheretranslate", &sphereTransform_.translate.x, 0.1f);
	ImGui::DragFloat3("sphererotate", &sphereTransform_.rotate.x, 0.1f);
	ImGui::DragFloat3("spherescale", &sphereTransform_.scale.x, 0.1f);
	ImGui::InputInt("SphereResource", &monsterBallResourceNum);
	ImGui::DragFloat4("LightColor", &directionalLight_.color.x, 1.0f);
	ImGui::DragFloat3("lightDirection", &directionalLight_.direction.x, 0.1f);
	ImGui::DragFloat2("uvScale", &SpriteuvTransform.scale.x, 0.1f);
	ImGui::DragFloat3("uvTranslate", &SpriteuvTransform.translate.x, 0.1f);
	ImGui::DragFloat("uvRotate", &SpriteuvTransform.rotate.z, 0.1f);
	ImGui::End();
}

void GameScene::Draw3D()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Draw(data1_[i], data2_[i], data3_[i],material[i],transform_,cameraTransform_,directionalLight_);
	}
	sphere_->Draw( sphereMaterial_,sphereTransform_,monsterBallResourceNum,cameraTransform_,directionalLight_);
}
void GameScene::Draw2D() {
	
		sprite_[0]->Draw(spritedataLeftTop_[0], spritedataRightDown_[0], spriteTransform_[0],SpriteuvTransform,spriteMaterial[0],uvResourceNum,directionalLight_);
	
	
}
void GameScene::Finalize()
{
	sphere_->Finalize();
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Finalize();
		sprite_[i]->Finalize();
	}
	
}
