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
	
	//クリア時間を入れる変数
	float testTime = 76.31f;
	//表示する4つの数字を入れる変数
	float displayNum[4];
	//数字画像
	Sprite numSprite[10];
	//小数点画像
	Sprite dotSprite;

	//何を選択しているか
	enum class Menu {
		Continue,
		Title
	}isSelect = Menu::Continue;
	//決定フラグ
	bool isReturn = false;

};

