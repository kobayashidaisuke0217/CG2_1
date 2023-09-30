#include "gameScene.h"


GameScene::~GameScene()
{
	
}

void GameScene::Initialize()
{
	blueMoon_ = BlueMoon::GetInstance();

	directXCommon_ = DirectXCommon::GetInstance();

	textureManager_ = Texturemanager::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,0.0f,-5.0f };
	uvResourceNum = textureManager_->Load("Resource/uvChecker.png");
	monsterBallResourceNum = textureManager_->Load("Resource/monsterBall.png");
	BlackResourceNum = textureManager_->Load("Resource/Black.png");
	material[0] = { 1.0f,1.0f,1.0f,1.0f };
	material[1] = { 1.0f,1.0f,1.0f,1.0f };
	spritedataLeftTop_ = { 0.0f,0.0f,0.0f,1.0f };
	spritedataRightDown_ = { 320.0f,180.0f,0.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	spriteMaterial = { 1.0f,1.0f,1.0f,1.0f };
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

	model_[0] = Model::CreateModelFromObj("Resource", "axis.obj");
	model_[1] = new Model();
	model_[1]->Initialize("Resource", "plane.obj");
	for (int i = 0; i < 2; i++) {
		modelMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
	}
	triangle_ = new Triangle();
	triangle_->Initialize(directionalLight_);
	for (int i = 0; i < 2; i++) {
		worldTransformtriangle_[i].Initialize();
	}
	sprite_ = new Sprite();
	sprite_->Initialize(  spritedataLeftTop_, spritedataRightDown_, directionalLight_);
	triangleIsAlive_ = false;
	spriteIsAlive_ = true;
	sphereIsAlive_ = true;
	modelIsAlive_ = false;
	GlovalVariables* globalVariables{};
	globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	GlovalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90.0f);
	globalVariables->AddItem(groupName, "Translation", worldTransformtriangle_[0].translation_);
	ApplyGlobalVariables();
}

void GameScene::Update()
{

	directionalLight_.direction = Normalise(directionalLight_.direction);
	
	
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


void GameScene::Draw()
{
	
	//3D描画準備
	blueMoon_->ModelPreDraw();
	Draw3D();
	//2D描画準備
	blueMoon_->SpritePreDraw();
	Draw2D();
}

void GameScene::Draw3D()
{
	
	
	if (triangleIsAlive_ ) {
		for (int i = 0; i < 2; i++) {
			triangle_->Draw(worldTransformtriangle_[i], viewProjection_, material[i]);
		}
	}
	if (modelIsAlive_ ) {
		for (int i = 0; i < 2; i++) {
			model_[0]->Draw(worldTransformtriangle_[i], viewProjection_, directionalLight_);
		}

	}
	if (sphereIsAlive_) {
		sphere_->Draw(sphereMaterial_, worldTransformtriangle_[1], monsterBallResourceNum, viewProjection_, directionalLight_);
	}
	blueMoon_->ModelPreDrawWireFrame();
	if (sphereIsAlive_) {
		sphere_->Draw(sphereMaterial_, worldTransformtriangle_[0], monsterBallResourceNum, viewProjection_, directionalLight_);
	}
	
}

void GameScene::ApplyGlobalVariables()
{
	GlovalVariables* globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	worldTransformtriangle_[0].translation_ = globalVariables->GetVector3Value(groupName, "Translation");
}

void GameScene::Draw2D() {

	if (spriteIsAlive_ ) {
		sprite_->Draw(spriteTransform_, SpriteuvTransform, spriteMaterial, 0);
	
	}

}
void GameScene::Finalize()
{
	
	delete sphere_;
	delete  sprite_;
	delete triangle_;
	for (int i = 0; i < 2; i++) {
		delete model_[i];

	}
	
}

