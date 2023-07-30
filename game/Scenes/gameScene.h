#pragma once
#include "Vector4.h"
#include<2d/Triangle.h>
#include "base/BlueMoon.h"
#include <base/ImGuiManger.h>
#include "Iscene.h"
#include <2d/Sprite.h>
#include<3d/Sphere.h>
#include<3d/Model.h>
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
	Vector4 data1_[2];
	Vector4 data2_[2];
	Vector4 data3_[2];
	Vector4 material[2];
	Triangle* triangle_[2];
	Transform transform_;
	Matrix4x4 worldMatrix_;
	Sphere* sphere_;
	Transform sphereTransform_;
	Vector4 sphereMaterial_;
	Matrix4x4 spherematrix_;
	//マトリックスデータ
	Transform cameraTransform_;
	//Light
	DirectionalLight directionalLight_;
	Model* model_[2];
	Transform modelTransform_[2];
	Vector4 modelMaterial_[2];
	uint32_t uvResourceNum;
	int monsterBallResourceNum;
 };

