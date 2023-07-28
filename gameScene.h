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
	~GameScene();
	void Initialize()override;
	void Update()override;
	void Draw2D();
	void Draw3D();
	void Draw()override;
	void Finalize();
private:
	BlueMoon* engine_;
	DirectXCommon* directX_;
	std::unique_ptr<Sprite>sprite_[2];
	Vector4 spritedataLeftTop_[2];
	Vector4 spritedataRightDown_[2];
	Transform spriteTransform_[2];
	Vector4 spriteMaterial[2];
	Transform SpriteuvTransform;
	Vector4 data1_[2];
	Vector4 data2_[2];
	Vector4 data3_[2];
	Vector4 material[2];
	std::unique_ptr<Triangle> triangle_[2];
	Transform transform_;
	Matrix4x4 worldMatrix_;
	std::unique_ptr<Sphere>sphere_;
	Transform sphereTransform_;
	Vector4 sphereMaterial_;
	Matrix4x4 spherematrix_;
	//マトリックスデータ
	Transform cameraTransform_;
	//Light
	DirectionalLight directionalLight_;
	std::unique_ptr<Model> model_;
	uint32_t uvResourceNum;
	int monsterBallResourceNum;
 };

