#pragma once
class Iscene
{
	virtual void Init()=0;

	virtual void Update()=0;

	virtual void Draw()=0;
protected:

	int stateNum;
};

