#pragma once
#include "Vector4.h"
#include "base/Triangle.h"
class GameScene
{
public:
	void Initialize(DirectXCommon*direct);
	void Update();
	void Draw();
	void Finalize();
private:
	DirectXCommon* directX_;
	Vector4 data1_[2];
	Vector4 data2_[2];
	Vector4 data3_[2];
	Triangle* triangle_[2];
};

