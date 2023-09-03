#pragma once
#include "Vector4.h"
#include "triangle.h"
#include "BlueMoon.h"
#include "ImGuiManger.h"
#include "Iscene.h"
#include "Sprite.h"
#include "Sphere.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
struct TriangleVertex {
	Vector4 v1;
	Vector4 v2;
	Vector4 v3;
};
class GameScene:public Iscene
{
public:
	GameScene();
	~GameScene();
	void Initialize()override;
	void Update()override;
	void Draw2D();
	void Draw3D();
	void Draw()override;
	void Finalize()override;
private:
	BlueMoon* engine_;
	DirectXCommon* directX_;
	Sprite* sprite_;
	
	Vector4 spritedataLeftTop_;
	Vector4 spritedataRightDown_;
	Transform spriteTransform_;
	Vector4 spriteMaterial;
	Transform SpriteuvTransform;
	Vector4 material[2];
	Triangle* triangle_[2];
	Matrix4x4 worldMatrix_;
	Sphere* sphere_;
	Vector4 sphereMaterial_;
	Matrix4x4 spherematrix_;
	//Light
	DirectionalLight directionalLight_;
	Model* model_[2];
	Vector4 modelMaterial_[2];
	uint32_t uvResourceNum;
	WorldTransform worldTransformtriangle_[2];
	ViewProjection viewProjection_;
	int monsterBallResourceNum;
	bool triangleIsAlive_;
	bool spriteIsAlive_;
	bool sphereIsAlive_;
	bool modelIsAlive_;
 };

