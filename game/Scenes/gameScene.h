#pragma once
#include "BlueMoon.h"
#include "MyMath.h"
#include "triangle.h"
#include "Iscene.h"
#include "Sprite.h"
#include "Sphere.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
#include "Texturemanager.h"

class GameScene:public Iscene
{
public:
	~GameScene();
	void Initialize()override;
	void Update()override;
	
	void Draw()override;
	void Finalize()override;
private:

	BlueMoon* blueMoon_;
	DirectXCommon* directXCommon_;
	Sprite* sprite_;
	Texturemanager* textureManager_;

	Vector4 spritedataLeftTop_;
	Vector4 spritedataRightDown_;
	Transform spriteTransform_;
	Vector4 spriteMaterial;
	Transform SpriteuvTransform;
	Vector4 material[2];
	Triangle* triangle_;
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
	int BlackResourceNum;
	bool triangleIsAlive_;
	bool spriteIsAlive_;
	bool sphereIsAlive_;
	bool modelIsAlive_;

	void Draw2D();
	void Draw3D();
 
};

