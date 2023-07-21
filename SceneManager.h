#pragma once
#include"Iscene.h"
class SceneManager:public Iscene 
{
public:
	enum Secene {
		TITLESCENE,
		GAMESCENE,
	};
	
	void Run();
	

};

