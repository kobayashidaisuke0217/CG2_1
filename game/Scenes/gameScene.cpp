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
	

	uvResourceNum = 0;
	engine_->LoadTexture("Resource/uvChecker.png", 0);
	monsterBallResourceNum = 1;
	engine_->LoadTexture("Resource/monsterBall.png", 1);

	
	triangleVertex_[0].v1= { -0.5f,-0.5f,0.5f,1.0f };
	triangleVertex_[0].v2= { 0.0f,0.0f,0.0f,1.0f };
	triangleVertex_[0].v3= { 0.5f,-0.5f,-0.5f,1.0f };
	triangleVertex_[1].v1 = { -0.5f,-0.5f,0.0f,1.0f };
	triangleVertex_[1].v2 = { 0.0f,0.5f,0.0f,1.0f };
	triangleVertex_[1].v3 = { 0.5f,-0.5f,0.0f,1.0f };

	material[0] = { 1.0f,1.0f,1.0f,1.0f };
	material[1] = { 1.0f,1.0f,1.0f,1.0f };
	triangleTransform_[0] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	triangleTransform_[1] = { {1.0f,1.0f,1.0f},{0.0f,5.0f,.0f},{0.0f,0.0f,0.0f} };
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
	model_[0]->Initialize(directX_, engine_, "Resource", "axis.obj", 2);
	model_[1] = new Model();
	model_[1]->Initialize(directX_, engine_, "Resource", "plane.obj", 3);
	for (int i = 0; i < 2; i++) {
		modelTransform_[i]= { {1.0f,1.0f,1.0f},{0.0f,1.6f,0.0f},{0.0f,0.0f,0.0f} };
		modelMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
	}
	
	
	
	
	
	
	for (int i = 0; i < 2; i++) {
		triangle_[i] =new Triangle();
		triangle_[i]->Initialize(directX_, engine_, triangleVertex_[i].v1, triangleVertex_[i].v2, triangleVertex_[i].v3, directionalLight_);
		
	}
sprite_ = new Sprite();
		sprite_->Initialize(directX_, engine_, spritedataLeftTop_, spritedataRightDown_, directionalLight_);
		triangleIsAlive_ = false;
		spriteIsAlive_ = false;
		sphereIsAlive_ = false;
		modelIsAlive_ = false;
}

void GameScene::Update()
{
	
	directionalLight_.direction= Normalise(directionalLight_.direction);
	
	
	if (ImGui::BeginTabBar("TabBar")) {
		if (ImGui::BeginTabItem("triangle1")) { 
			ImGui::Checkbox("IsAlive", &triangleIsAlive_);
			ImGui::ColorEdit3("triangleColor1",&material[0].x);
			ImGui::DragFloat3("triangletranslate", &triangleTransform_[0].translate.x, 0.1f);
			ImGui::DragFloat3("trianglerotate", &triangleTransform_[0].rotate.x, 0.1f);
			ImGui::DragFloat3("trianglescale", &triangleTransform_[0].scale.x, 0.1f);
          
	      

		   ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("triangle2")) {
			ImGui::Checkbox("IsAlive", &triangleIsAlive_);
			ImGui::ColorEdit3("triangleColor", &material[1].x);
			ImGui::DragFloat3("triangletranslate", &triangleTransform_[1].translate.x, 0.1f);
			ImGui::DragFloat3("trianglerotate", &triangleTransform_[1].rotate.x, 0.1f);
			ImGui::DragFloat3("trianglescale", &triangleTransform_[1].scale.x, 0.1f);


			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Sphere")) {
			ImGui::Checkbox("IsAlive", &sphereIsAlive_);
		 ImGui::DragFloat3("spheretranslate", &sphereTransform_.translate.x, 0.1f);
	     ImGui::DragFloat3("sphererotate", &sphereTransform_.rotate.x, 0.1f);
	     ImGui::DragFloat3("spherescale", &sphereTransform_.scale.x, 0.1f);
	     ImGui::InputInt("SphereResource", &monsterBallResourceNum);
		 ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Texture")) {
			ImGui::Checkbox("IsAlive", &spriteIsAlive_);
			ImGui::DragFloat3("spritetranslate", &spriteTransform_.translate.x, 0.1f);
			ImGui::DragFloat2("uvScale", &SpriteuvTransform.scale.x, 0.1f);
			ImGui::DragFloat3("uvTranslate", &SpriteuvTransform.translate.x, 0.1f);
			ImGui::DragFloat("uvRotate", &SpriteuvTransform.rotate.z, 0.1f);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera")) {
			ImGui::DragFloat3("CameraTranslate", &cameraTransform_.translate.x, 0.01f);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Light")) {
           ImGui::ColorEdit3("LightColor", &directionalLight_.color.x);
	       ImGui::DragFloat3("lightDirection", &directionalLight_.direction.x, 0.1f);
		   ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Model")) {
			ImGui::Checkbox("IsAlive", &modelIsAlive_);
			ImGui::DragFloat3("modeltranslate", &modelTransform_[0].translate.x,0.01f);
			ImGui::DragFloat3("modelrotate", &modelTransform_[0].rotate.x, 0.01f);
			ImGui::DragFloat3("modelscale", &modelTransform_[0].scale.x, 0.01f);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Model2")) {
			ImGui::Checkbox("IsAlive", &modelIsAlive_);
			ImGui::DragFloat3("modeltranslate", &modelTransform_[1].translate.x, 0.01f);
			ImGui::DragFloat3("modelrotate", &modelTransform_[1].rotate.x, 0.01f);
			ImGui::DragFloat3("modelscale", &modelTransform_[1].scale.x, 0.01f);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	
	
	

	
	
	ImGui::Begin("Scene");
	ImGui::InputInt("SceneNum", &sceneNum);
	if (sceneNum > 1) {
		sceneNum = 1;
	}
	ImGui::End();
}

void GameScene::Draw3D()
{
	if (triangleIsAlive_ == true) {
		for (int i = 0; i < 2; i++) {
			triangle_[i]->Draw(triangleTransform_[i], cameraTransform_, material[i]);
		}
	}
	if (modelIsAlive_ == true) {
		for (int i = 0; i < 2; i++) {
			model_[i]->Draw(sphereMaterial_, modelTransform_[i], 3, cameraTransform_, directionalLight_);
		}
	}
	if (sphereIsAlive_ == true) {
		sphere_->Draw(sphereMaterial_, sphereTransform_, monsterBallResourceNum, cameraTransform_, directionalLight_);
	}

}
void GameScene::Draw()
{
	Draw3D();
	Draw2D();
}
void GameScene::Draw2D() {
	if (spriteIsAlive_ == true) {
		sprite_->Draw(spriteTransform_, SpriteuvTransform, spriteMaterial, 3);
	}
	
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
