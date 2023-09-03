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

	textureManager_ = Texturemanager::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	uvResourceNum = textureManager_->Load("Resource/uvChecker.png");
	monsterBallResourceNum = textureManager_->Load("Resource/monsterBall.png");

	
	

	material[0] = { 1.0f,1.0f,1.0f,1.0f };
	material[1] = { 1.0f,1.0f,1.0f,1.0f };
	

	spritedataLeftTop_ = {0.0f,0.0f,0.0f,1.0f};
	spritedataRightDown_ = {320.0f,180.0f,0.0f,1.0f};
	spriteTransform_  = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};

	
	spriteMaterial = {1.0f,1.0f,1.0f,1.0f};
	
	sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	SpriteuvTransform =
	{ 
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};
	directionalLight_ = { {1.0f,1.0f,1.0f,1.0f},{0.0f,-1.0f,0.0f},1.0f };
	sphere_ = new Sphere();
	sphere_->Initialize();
	model_[0] = new Model();
	model_[0]->Initialize( "Resource", "axis.obj");
	model_[1] = new Model();
	model_[1]->Initialize( "Resource", "plane.obj");
	for (int i = 0; i < 2; i++) {
		modelMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
	}
	triangle_[0] =new Triangle();
		triangle_[0]->Initialize( directionalLight_);
	for (int i = 0; i < 2; i++) {
		worldTransformtriangle_[i].Initialize();
	}
sprite_ = new Sprite();
		sprite_->Initialize( spritedataLeftTop_, spritedataRightDown_, directionalLight_);
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
			ImGui::DragFloat3("triangletranslate", &worldTransformtriangle_[0].translation_.x, 0.1f);
			ImGui::DragFloat3("trianglerotate", &worldTransformtriangle_[0].rotation_.x, 0.1f);
			ImGui::DragFloat3("trianglescale", &worldTransformtriangle_[0].scale_.x, 0.1f);
          
	      

		   ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("triangle2")) {
			ImGui::Checkbox("IsAlive", &triangleIsAlive_);
			ImGui::ColorEdit3("triangleColor", &material[1].x);
			ImGui::DragFloat3("triangletranslate", &worldTransformtriangle_[1].translation_.x, 0.1f);
			ImGui::DragFloat3("trianglerotate", &worldTransformtriangle_[1].rotation_.x, 0.1f);
			ImGui::DragFloat3("trianglescale", &worldTransformtriangle_[1].scale_.x, 0.1f);


			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Sphere")) {
			ImGui::Checkbox("IsAlive", &sphereIsAlive_);
	
	     ImGui::InputInt("SphereResource", &monsterBallResourceNum);
		 ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Texture")) {
			ImGui::Checkbox("IsAlive", &spriteIsAlive_);
			ImGui::DragFloat3("spritetranslate", &spriteTransform_.translate.x, 0.1f);
			ImGui::DragFloat3("spriterotate", &spriteTransform_.rotate.x, 0.1f);
			ImGui::DragFloat3("spritescale", &spriteTransform_.scale.x, 0.1f);
			ImGui::DragFloat2("uvScale", &SpriteuvTransform.scale.x, 0.1f);
			ImGui::DragFloat3("uvTranslate", &SpriteuvTransform.translate.x, 0.1f);
			ImGui::DragFloat("uvRotate", &SpriteuvTransform.rotate.z, 0.1f);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera")) {
			ImGui::DragFloat3("CameraTranslate", &viewProjection_.translation_.x, 0.01f);
			ImGui::DragFloat3("CameraRotate", &viewProjection_.rotation_.x, 0.01f);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Light")) {
           ImGui::ColorEdit3("LightColor", &directionalLight_.color.x);
	       ImGui::DragFloat3("lightDirection", &directionalLight_.direction.x, 0.1f);
		   ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Model")) {
			ImGui::Checkbox("IsAlive", &modelIsAlive_);
			
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Model2")) {
			ImGui::Checkbox("IsAlive", &modelIsAlive_);
			
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	
	worldTransformtriangle_[0].UpdateMatrix();
	worldTransformtriangle_[1].UpdateMatrix();

	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
	
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
			triangle_[0]->Draw(worldTransformtriangle_[i], viewProjection_, material[i]);
		}
	}
	if (modelIsAlive_ == true) {
		for (int i = 0; i < 2; i++) {
			model_[0]->Draw(worldTransformtriangle_[i],  viewProjection_, directionalLight_);
		}
		
	}
	if (sphereIsAlive_ == true) {
		sphere_->Draw(sphereMaterial_, worldTransformtriangle_[0], monsterBallResourceNum, viewProjection_, directionalLight_);
	}

}
void GameScene::Draw()
{
	Draw3D();
	Draw2D();
}
void GameScene::Draw2D() {
	if (spriteIsAlive_ == true) {
		//sprite_->Draw(spriteTransform_, SpriteuvTransform, spriteMaterial, 3);
		sprite_->Draw(worldTransformtriangle_[0], SpriteuvTransform, spriteMaterial, uvResourceNum);
	}
	
}
void GameScene::Finalize()
{
	
	delete sphere_;
	
delete  sprite_;delete triangle_[0];
		delete model_[0];
	for (int i = 0; i < 2; i++) {
		
	
	}
}
