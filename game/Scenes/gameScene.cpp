#include "gameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	engine_ = BlueMoon::GetInstance();
	
	directX_ = DirectXCommon::GetInstance();
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

	spritedataLeftTop_ = {0.0f,0.0f,0.0f,1.0f};
	spritedataRightDown_ = {320.0f,180.0f,0.0f,1.0f};
	spriteTransform_  = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};

	
	spriteMaterial = {1.0f,1.0f,1.0f,1.0f};
	sphereTransform_= { {1.0f,1.0f,1.0f},{0.0f,1.6f,0.0f},{0.0f,0.0f,0.0f} };
	sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	SpriteuvTransform =
	{ 
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	directionalLight_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
	sphere_ = new Sphere();
	sphere_->Initialize(directX_, engine_);
	model_[0] = new Model();
	model_[0]->Initialize(directX_, engine_, "Resource", "axis.obj", 0, directionalLight_);
	model_[1] = new Model();
	model_[1]->Initialize(directX_, engine_, "Resource", "plane.obj", 1, directionalLight_);
	for (int i = 0; i < 2; i++) {
		modelTransform_[i]= { {1.0f,1.0f,1.0f},{0.0f,1.6f,0.0f},{0.0f,0.0f,0.0f} };
		modelMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
	}

	uvResourceNum = 2;
	engine_->LoadTexture("Resource/uvChecker.png",2);
	monsterBallResourceNum = 3;
	engine_->LoadTexture("Resource/monsterBall.png",3);
	
	
	
	
	
	for (int i = 0; i < 2; i++) {
		triangle_[i] =new Triangle();
		triangle_[i]->Initialize(directX_, engine_, data1_[i], data2_[i], data3_[i], directionalLight_);
		
	}
sprite_ = new Sprite();
		sprite_->Initialize(directX_, engine_, spritedataLeftTop_, spritedataRightDown_, directionalLight_);
}

void GameScene::Update()
{
	transform_.rotate.y += 0.01f;
	directionalLight_.direction= Normalise(directionalLight_.direction);
	/*material[0].y -= 0.1f;
	material[0].x -= 0.1f;*/
	ImGui::Begin("Window");
	ImGui::DragFloat3("CameraTranslate", &cameraTransform_.translate.x, 0.01f);
	ImGui::DragFloat3("spritetranslate", &spriteTransform_.translate.x, 0.1f);
	ImGui::DragFloat3("spheretranslate", &sphereTransform_.translate.x, 0.1f);
	ImGui::DragFloat3("sphererotate", &sphereTransform_.rotate.x, 0.1f);
	ImGui::DragFloat3("spherescale", &sphereTransform_.scale.x, 0.1f);
	ImGui::InputInt("SphereResource", &monsterBallResourceNum);

	ImGui::ColorEdit3("LightColor", &directionalLight_.color.x);
	ImGui::DragFloat3("lightDirection", &directionalLight_.direction.x, 0.1f);
	ImGui::DragFloat2("uvScale", &SpriteuvTransform.scale.x, 0.1f);
	ImGui::DragFloat3("uvTranslate", &SpriteuvTransform.translate.x, 0.1f);
	ImGui::DragFloat("uvRotate", &SpriteuvTransform.rotate.z, 0.1f);

	ImGui::ColorEdit3("triangleColor1",&material[0].x);
	ImGui::ColorEdit3("triangleColor2", &material[1].x);
	
	ImGui::End();
}

void GameScene::Draw3D()
{
	for (int i = 0; i < 2; i++) {
		triangle_[i]->Draw(transform_, cameraTransform_, material[i] );
	}
	for (int i = 0; i < 2; i++) {
		model_[i]->Draw(sphereMaterial_, modelTransform_[i], 0, cameraTransform_);
	}
	sphere_->Draw(sphereMaterial_, sphereTransform_, monsterBallResourceNum, cameraTransform_, directionalLight_);


}
void GameScene::Draw()
{
	Draw3D();
	Draw2D();
}
void GameScene::Draw2D() {
	
		sprite_->Draw( spriteTransform_,SpriteuvTransform,spriteMaterial,0);
	
	
}
void GameScene::Finalize()
{
	
	delete sphere_;
	
delete  sprite_;
	for (int i = 0; i < 2; i++) {
		delete triangle_[i];
		delete model_[i];
	
	}
}
