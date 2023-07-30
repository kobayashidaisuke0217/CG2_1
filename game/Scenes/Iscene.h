#pragma once
enum  Scene {
	TITLE_SCENE,
	GAME_SCENE,
};
class Iscene
{
public:
	virtual void Initialize()=0;

	virtual void Update()=0;

	virtual void Draw()=0;

	virtual void Finalize() = 0;
	 int GetSceneNum() { return sceneNum; }
protected:

	static int sceneNum;
};

