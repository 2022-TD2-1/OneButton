#pragma once
#include "IScene.h"
#include "Matrix.h"
#include "Model.h"
#include "Object3D.h"
#include "Sprite.h"
#include "Camera.h"
#include "Input.h"
#include <Player.h>
#include <Sprite.h>
using namespace Input;
class ResultScene
	: public IScene
{
public:

	void Init() override;
	void Update() override;
	void DrawBack() override;
	void Draw3D() override;
	void DrawSprite() override;

private:
	Camera camera;
	//テスト用画像
	Sprite testSprite;

	//数字画像
	Sprite numSprite[10];
	Sprite testnumSprite;

	//何を選択しているか
	enum class Menu {
		Continue,
		Title
	}isSelect = Menu::Continue;
	//決定フラグ
	bool isReturn = false;

};

