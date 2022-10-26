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
#include <GameTimer.h>
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
	float clearTime = 03.31f;
	float setTimer;
	int t;
	//表示する4つの数字を入れる変数
	float displayNum[5];
	//表示させる画像
	Sprite displayNumSprite[5];
	//数字画像
	Sprite numSprite[10];
	//小数点画像
	Sprite dotSprite;
	//テキスト画像
	Sprite menuTxt[2];
	Sprite selectSprite;

	Object3D rankTxtObj;
	Object3D rankObj[4];
	void UpdateNum();	//数字を更新する

	int rank;
	bool isDisplayRank = false;
	void Rank();		//クリアタイムに応じたランク

	//何を選択しているか
	enum class Menu {
		Continue,
		Title
	}isSelect = Menu::Continue;
	//決定フラグ
	bool isReturn = false;

	Object3D skyDome;
	Object3D clearObj;
	Object3D gameOverObj;

	GameTimer* timer_ = nullptr;
	//操作を受け付けない時間
	int controlTime;
	Player* player_ = nullptr;
	bool isResultState;
};

