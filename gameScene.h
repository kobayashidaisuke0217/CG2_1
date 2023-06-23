#pragma once
#include "Vector4.h"
#include "base/Triangle.h"
#include "base/MyEngine.h"
#include "ImGuiManger.h"
#include"Sprite.h"
class GameScene
{
public:
	void Initialize(MyEngine*engine,DirectXCommon*direct);
	void Update();
	void Draw2D();
	void Draw3D();
	void Finalize();
private:
	MyEngine* engine_;
	DirectXCommon* directX_;
	Sprite* sprite_[2];
	Vector4 spritedataLeftTop_[2];
	Vector4 spritedataRightDown_[2];
	Transform spriteTransform_[2];
	Vector4 spriteMaterial[2];
	Vector4 data1_[2];
	Vector4 data2_[2];
	Vector4 data3_[2];
	Vector4 material[2];
	Triangle* triangle_[2];
	Transform transform_;
	Matrix4x4 worldMatrix_;
	//マトリックスデータ
	Transform cameraTransform_;
};

