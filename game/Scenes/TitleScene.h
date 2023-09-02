#pragma once
#include "Iscene.h"
#include "Input/Input.h"
class TitleScene:public Iscene
{
private:
	int count;
public:
	 void Initialize() override;

	 void Update() override;

	 void Draw() override;
	 void Finalize()override;
private:
	Input* input=nullptr;
};

