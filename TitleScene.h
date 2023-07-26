#pragma once
#include "Iscene.h"
class TitleScene:public Iscene
{
private:
	int count;
public:
	 void Initialize() override;

	 void Update() override;

	 void Draw() override;
};

