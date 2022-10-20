#pragma once
#include "IScene.h"
#include "Essentials.h"
class SceneManager
{
public:
	static void Init();
	static void Update();
	static void Draw3D();
	static void DrawSprite();
	static void DrawBack();

	template <class NextScene> 
	static void Transition();

	static unique_ptr<IScene> currentScene;
};